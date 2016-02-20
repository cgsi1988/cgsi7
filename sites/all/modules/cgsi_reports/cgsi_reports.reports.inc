<?php
/**
 * @file
 * Report specific code.
 */

/**
 * Menu Callback; Generate a report showing monthly membership statistics.
 */
function cgsi_reports_membership_by_month() {
	// Finding arguments this way so that we do not have to use wildcard menu
	// loaders. This just makes it easier for our links to show up in admin_menu.
	$year = arg(4);
	$year = isset($year) ? (int) $year : (int) date('Y');

	if (!is_int($year)) {
		drupal_set_message('Invalid argument.');
		drupal_goto('admin/users/reports/membership');
	}

	drupal_set_title(t('Membership by Month for @year', array('@year' => $year)));
	$data = cgsi_reports_membership_by_month_generate($year);

	$theme_vars = array();
	$theme_vars['rows'] = $data;
	$output .= theme('table', $theme_vars);

	$output .= theme('item_list', array('items' => array(l(t('Download CSV'), 'admin/user/reports/membership/csv'))));

	return $output;
}

/**
 * Menu Callback; Download CSV version of monthly membership statistics.
 */
function cgsi_reports_membership_by_month_csv() {
	// Finding arguments this way so that we do not have to use wildcard menu
	// loaders. This just makes it easier for our links to show up in admin_menu.
	$year = arg(5);
	$year = isset($year) ? (int) $year : (int) date('Y');

	if (!is_int($year)) {
		drupal_set_message('Invalid argument.');
		drupal_goto('admin/users/reports/membership');
	}

	$data = cgsi_reports_membership_by_month_generate($year);
	cgsi_reports_table_export('cgsi-membership-by-month-' . check_plain($year) . '.csv', NULL, $data);
}

/**
 * Collect data for the membership by month report.
 *
 * @param $year
 *   Numeric representation of the year to collect data for.
 *
 * @return
 *   An array of data suitable for use by theme_table().
 */
function cgsi_reports_membership_by_month_generate($year) {
	// Setup some structure for our data.
	$months = array('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec');
	$data = array_fill_keys($months, array());

	// Get information about possible sources for new members.
	// @see profile.module {profile_value}.fid = 29.
	$value = db_query('SELECT options FROM {profile_field} WHERE fid = 29')->fetchField();
	$values = preg_split("/[,\n\r]/", $value);
	$sources = array();
	foreach ($values as $value) {
		$value = trim($value);
		if ($value) {
			$sources[] = $value;
		}
	}

	$levels = db_query("SELECT options FROM {profile_field} WHERE name = 'profile_membership_level'")->fetchField();
	$levels = preg_split("/[,\n\r]/",  $levels);
	$levels = array_filter($levels);
	$terms = db_query("SELECT options FROM {profile_field} WHERE name = 'profile_membership_term'")->fetchField();
	$terms = preg_split("/[,\n\r]/",  $terms);
	$terms = array_filter($terms);

	foreach ($data as $key => $value) {
		foreach ($levels as $level) {
			foreach ($terms as $term) {
				$data[$key]['new'][$level . ' - ' . $term] = 0;
				$data[$key]['renew'][$level . ' - ' . $term] = 0;
				$data[$key]['total_active'] = 0;
				$data[$key]['total_family'] = 0;
			}
		}
	}

	// Number new.
	$results = db_query("SELECT uid, DATE_FORMAT(FROM_UNIXTIME(created), '%b') AS mon FROM {uc_roles_history} WHERE activity = 'new' AND YEAR(FROM_UNIXTIME(created)) = {$year} GROUP BY uid");
	foreach ($results as $row) {
		$row_profile_field = _cgsi_reports_profile_field($row->uid);
		$data[$row->mon]['new'][$row_profile_field['profile_membership_level']  . ' - ' . $row_profile_field['profile_membership_term']]++;
		$data[$row->mon]['new']['by_state'][strtoupper($row_profile_field['profile_state'])]++;
		$data[$row->mon]['new_total']++;
		// Source of membership.
		if (isset($row_profile_field['profile_membership_source'])) {
			$data[$row->mon]['source'][$row_profile_field['profile_membership_source']]++;
		}
	}

	// Number canceled.
	$results = db_query("SELECT count(DISTINCT(uid)) AS num, DATE_FORMAT(FROM_UNIXTIME(modified), '%b') AS mon FROM {cgsi_status_history} WHERE status = 'inactive_cancel' AND YEAR(FROM_UNIXTIME(modified)) = {$year}");
	foreach ($results as $row) {
		$data[$row->mon]['inactive_cancel'] = $row->num;
	}

	// Number died.
	$results = db_query("SELECT count(DISTINCT(uid)) AS num, DATE_FORMAT(FROM_UNIXTIME(modified), '%b') AS mon FROM {cgsi_status_history} WHERE status = 'inactive_death' AND YEAR(FROM_UNIXTIME(modified)) = {$year} GROUP BY mon");
	foreach ($results as $row) {
		$data[$row->mon]['inactive_death'] = $row->num;
	}

	// Number expired.
	$results = db_query("SELECT count(DISTINCT(uid)) AS num, DATE_FORMAT(FROM_UNIXTIME(created), '%b') AS mon FROM {uc_roles_history} WHERE activity = 'revoke' AND YEAR(FROM_UNIXTIME(created)) = {$year} GROUP BY mon");
	foreach ($results as $row) {
		$data[$row->mon]['expired'] = $row->num;
	}

	// Number of people who expired and then renewed in the same month.
	$results = db_query("SELECT count(DISTINCT(uid)) AS num, DATE_FORMAT(FROM_UNIXTIME(created), '%b') AS mon FROM {uc_roles_history} WHERE activity = 'renew' AND YEAR(FROM_UNIXTIME(created)) = {$year} GROUP BY mon");
	foreach ($results as $row) {
		$data[$row->mon]['expired_renewed'] = $row->num;
	}

	// Number renew.
	$results = db_query("SELECT uid, DATE_FORMAT(FROM_UNIXTIME(created), '%b') AS mon FROM {uc_roles_history} WHERE activity = 'renew' AND YEAR(FROM_UNIXTIME(created)) = {$year} GROUP BY uid");
	foreach ($results as $row) {
		$row_profile_field = _cgsi_reports_profile_field($row->uid);
		$data[$row->mon]['renew'][$row_profile_field['profile_membership_level']  . ' - ' . $row_profile_field['profile_membership_term']]++;
		$data[$row->mon]['renew_total']++;
	}

	/* Total active members.
	 $results = db_query('SELECT count(DISTINCT(uid)) AS num, DATE_FORMAT(FROM_UNIXTIME(modified), '%b') AS mon FROM {cgsi_status_history} cs WHERE cs.status = "active" AND YEAR(FROM_UNIXTIME(modified)) = %d GROUP BY mon ORDER BY modified', '%b', $year);
	while ($row = db_fetch_array($results)) {
	//$data[$row->mon]['total_active'] = $row->num;
	} */

	// Total active members for each month based on their last known active status
	// before DATE.
	for ($i = 1; $i <= 12; $i++) {
		// Figure out the last day of each month.
		$timestamp_start = strtotime($year . '-' . $i . '-01');
		// Only need to do this for months that have already passed.
		if ($timestamp_start <= time()) {
			$timestamp_end = strtotime('-1 second', strtotime('+1 month', $timestamp_start));
			$timestamp_end = strtotime(date('Y-m-d 23:59:00', $timestamp_end));
			$data[$months[$i - 1]]['total_active'] = db_query("SELECT count(DISTINCT(uid)) AS num, csh.uid FROM {cgsi_status_history} csh WHERE (SELECT status FROM {cgsi_status_history} WHERE uid = csh.uid AND modified <= {$timestamp_end} ORDER BY modified DESC LIMIT 1) = 'active'")->fetchField();
			$data[$months[$i - 1]]['total_family'] = db_query("SELECT count(DISTINCT(csh.uid)) AS num, csh.uid FROM {cgsi_status_history} csh INNER JOIN {profile_value} pv ON pv.uid = csh.uid WHERE pv.fid = 24 AND CHAR_LENGTH(pv.value) > 0 AND (SELECT status FROM {cgsi_status_history} WHERE uid = csh.uid AND modified <= $timestamp_end ORDER BY modified DESC LIMIT 1) = 'active'")->fetchField();

			// As long as we are in this loop lets calculate the number of members
			// who dropped and then renewed within the month.
			$data[$months[$i - 1]]['drop_renew'] = db_query("SELECT count(DISTINCT(uid)) AS num FROM uc_roles_history WHERE created >= {$timestamp_start} AND created <= {$timestamp_end} AND activity='revoke' AND uid IN (SELECT uid FROM uc_roles_history WHERE created >= {$timestamp_start} AND created <= {$timestamp_end} AND activity='renew')")->fetchField();
		}
		else {
			$data[$months[$i-1]]['total_active'] = 0;
			$data[$months[$i - 1]]['drop_renew'] = 0;
		}
	}

	// Format collected data into a table.
	$row_names = array();

	// Build array of row names (membership term/level).
	foreach ($data[$months[0]]['new'] as $row_name => $row_value) {
		// Make sure we skip the  'by_state' array.
		if ($row_name == 'by_state') {
			continue;
		}
		$row_names[] = $row_name;
	}

	$months_row = array('Month');
	$months_row = array_merge($months_row, $months);

	$new_member_rows = array();
	$new_members_by_state = array();
	$renew_member_rows = array();
	$renew_after_drop_rows = array('Renew after Drop');
	$comp_members_rows = array('Complimentary');
	$cancel_rows = array('Cancel');
	$death_rows = array('Death');
	$expired_rows = array('Dropped');
	$current_members_rows = array('Current Members');
	$family_members_rows = array('2nd Household Members');
	$current_totals_rows = array('Total Members');

	foreach ($row_names as $row_name) {
		$new_member_row = array($row_name);
		$renew_member_row = array($row_name);
		foreach ($months as $month_name) {
			// New members, for the month that signed up for $row_name (Term/Level).
			$new_member_row[$month_name] = $data[$month_name]['new'][$row_name];
			// New members by state/province.
			foreach ($months as $mname) {
				if (isset($data[$mname]['new']['by_state'])) {
					foreach ($data[$mname]['new']['by_state'] as $state => $number) {
						if ($state) {
							if (!isset($new_members_by_state[$state])) {
								$new_members_by_state[$state] = array();
							}
							$new_members_by_state[$state][$mname] = $number;
						}
					}
				}
			}

			// Renew members, for the month that signed up for $row_name (Term/Level).
			$renew_member_row[$month_name] = $data[$month_name]['renew'][$row_name];
			// Complimentary memberhsips.
			//$comp_members_rows[$month_name] = isset($data[$month_name]['comp_total']) ? $data[$month_name]['comp_total'] : 0;
			$comp_members_rows[$month_name] = 0;
			// Cancelled members for the month.
			$cancel_rows[$month_name] = isset($data[$month_name]['inactive_cancel']) ? $data[$month_name]['inactive_cancel'] : 0;
			// Deathed members for the month.
			$death_rows[$month_name] = isset($data[$month_name]['inactive_death']) ? $data[$month_name]['inactive_death'] : 0;
			// Expired members for the month.
			$expired_rows[$month_name] = isset($data[$month_name]['expired']) ? $data[$month_name]['expired'] : 0;
			// Current active, and family members.
			$current_members_rows[$month_name] = $data[$month_name]['total_active'];
			$family_members_rows[$month_name] = $data[$month_name]['total_family'];
			$renew_after_drop_rows[$month_name] = $data[$month_name]['drop_renew'];
			$current_totals_rows[$month_name] = $current_members_rows[$month_name] + $family_members_rows[$month_name];
		}
		$new_member_rows[] = $new_member_row;
		$renew_member_rows[] = $renew_member_row;
	}

	// Fill in members by state array for months with no value.
	foreach ($new_members_by_state as $key => $value) {
		foreach ($months as $month_name) {
			if (!isset($new_members_by_state[$key][$month_name])) {
				$new_members_by_state[$key][$month_name] = 0;
			}
		}
	}

	// Make sure member by state columns are in the right order.
	$new_members_by_state_clone = $new_members_by_state;
	$new_members_by_state = array();
	foreach ($months as $month_name) {
		foreach ($new_members_by_state_clone as $state => $num) {
			$new_members_by_state[$state][$month_name] = $num[$month_name];
		}
	}

	// Finally, add row names to each one.
	foreach ($new_members_by_state as $key => $value) {
		array_unshift($new_members_by_state[$key], t('New Members From: @state', array('@state' => $key)));
	}
	// Sort alphabetically.
	ksort($new_members_by_state);

	// Membership source info and some totals.
	$source_rows = array();
	$new_totals_row = array();
	$renew_totals_row = array();
	foreach ($sources as $source_name) {
		$source_row = array($source_name);
		foreach ($months as $month_name) {
			$source_row[$month_name] = isset($data[$month_name]['source'][$source_name]) ? $data[$month_name]['source'][$source_name] : 0;
			$new_totals_row[$month_name] = isset($data[$month_name]['new_total']) ? $data[$month_name]['new_total'] : 0;
			$renew_totals_row[$month_name] = isset($data[$month_name]['renew_total']) ? $data[$month_name]['renew_total'] : 0;
		}
		$source_rows[] = $source_row;
	}

	$rows = array();
	$rows[] = array(t('Membership by Month'), '', '', '', '', '', '', '', '', '', '', '', '');
	// Blank row.
	$rows[] = array_pad(array(), 13, '');
	$rows[] = $months_row;
	array_unshift($new_totals_row, t('New Members'));
	$rows = array_merge($rows, array($new_totals_row));
	$rows = array_merge($rows, $new_member_rows);
	$rows[] = $comp_members_rows;
	$rows[] = $cancel_rows;
	$rows[] = $death_rows;
	$rows[] = $expired_rows;
	$rows[] = $renew_after_drop_rows;
	// Blank row.
	$rows[] = array_pad(array(), 13, '');
	$rows[] = $current_members_rows;
	$rows[] = $family_members_rows;
	$rows[] = $current_totals_rows;
	// Blank row.
	$rows[] = array_pad(array(), 13, '');
	$rows = array_merge($rows, $source_rows);
	// Blank row.
	$rows[] = array_pad(array(), 13, '');
	array_unshift($renew_totals_row, t('Renewals'));
	$rows = array_merge($rows, array($renew_totals_row));
	$rows = array_merge($rows, $renew_member_rows);
	// Blank row.
	$rows[] = array_pad(array(), 13, '');
	// Blank row.
	$rows[] = array_pad(array(), 13, '');

	// Add in state rows.
	foreach ($new_members_by_state as $row) {
		$rows[] = $row;
	}

	return $rows;
}

/**
 * Menu callback; Generate report showing total number of currently active
 * members for each state/province.
 */
function cgsi_reports_membership_mailing() {
	drupal_set_title(t('CGSI Membership Mailing', array('@year' => $year)));
	$data = cgsi_reports_membership_mailing_generate();

	$output = '';
	foreach ($data as $key => $value) {
		$theme_vars = array();
		$theme_vars['rows'] = $value['rows'];
		$theme_vars['header'] = $value['headers'];
		$output .= theme('table', $theme_vars);
	}

	$output .= theme('item_list', array('items' => array(l(t('Download CSV'), 'admin/user/reports/membership-mailing/csv'))));
	return $output;
}

/**
 * Menu callback; Export membership mailing reports as CSV.
 */
function cgsi_reports_membership_mailing_csv() {
	$data = cgsi_reports_membership_mailing_generate();
	$rows = array();
	foreach ($data as $key => $value) {
		$rows = array_merge($rows, $value['headers']);
		$rows = array_merge($rows, $value['rows']);
	}
	cgsi_reports_table_export('membership-mailing.csv', NULL, $rows);
}

/**
 * Calculate data for the membership mailing report.
 *
 * @return
 *   An array of array's which each contain 'headers' and 'rows' suitable for
 *   use by theme_table().
 */
function cgsi_reports_membership_mailing_generate() {
	// Initiate some variables.
	$us_data = array();
	$us_total = 0;
	$ca_data = array();
	$ca_total = 0;
	$other_data = array();
	$other_total = 0;

	// Get state names.
	$state_names = array();
	$results = db_query('SELECT zone_code, zone_name FROM {uc_zones} WHERE zone_country_id = 840');
	foreach ($results as $row) {
		$state_names[strtolower($row->zone_code)] = $row->zone_name;
	}

	$state_names['z n/a'] = t('Unknown'); // Place holder for members with no state.

	// Get a list of all currently active users.
	$results = db_query("SELECT pv.value AS state, pv2.value AS country, cs.uid FROM {cgsi_status} cs INNER JOIN {profile_value} pv ON pv.uid = cs.uid INNER JOIN {profile_value} pv2 ON pv2.uid = cs.uid WHERE cs.status = 'active' AND pv.fid = 6 AND pv2.fid = 12");
	foreach ($results as $row) {
		$country = check_plain(strtolower($row->country));
		$state = check_plain(strtolower($row->state));

		if ($country == 'united states') {
			// If the state is not filled out this data isn't very helpful.
			$state = isset($state_names[$state]) ? $state : 'z n/a';
			if (isset($us_data[$state])) {
				$us_data[$state][1]++;
			}
			else {
				$us_data[$state] = array($state_names[$state], 1);
			}
			$us_total++;
		}
		else if ($country == 'canada') {
			if (isset($ca_data[$state])) {
				$ca_data[$state][1]++;
			}
			else {
				$ca_data[$state] = array(ucwords($state), 1);
			}
			$ca_total++;
			// Canada also gets counted in the "Outside USA" section.
			$other_total++;
		}
		else {
			if (isset($other_data[$country])) {
				$other_data[$country][1]++;
			}
			else {
				$other_data[$country] = array(ucwords($country), 1);
			}
			$other_total++;
		}
	}

	$output = array();

	$rows = array();
	ksort($us_data);
	$rows = array_merge($rows, $us_data);
	$rows[] = array(t('Total USA'), $us_total);
	$rows[] = array(t('Outside USA Total'), $other_total);
	$output['us'] = array('headers' => array(t('State'), t('Total')), 'rows' => $rows);

	// Blank.
	$rows = array();
	ksort($other_data);
	$rows = array_merge($rows, $other_data);
	$rows[] = array('Total', $other_total);
	$output['other'] = array('headers' => array(t('Outside USA'), t('Total')), 'rows' => $rows);

	// Blank
	$rows = array();
	ksort($ca_data);
	$rows = array_merge($rows, $ca_data);
	$rows[] = array(t('Total'), $ca_total);
	$output['canada'] = array('headers' => array(t('Canadian Province'), t('Total')), 'rows' => $rows);

	return $output;
}

/**
 * Form Builder; Weekly membership activity report menu callback.
 */
function cgsi_reports_membership_weekly($form_state) {
	$start_date = check_plain($_GET['start_date']);
	$end_date = check_plain($_GET['end_date']);

	$form = array();
	$form['start_date'] = array(
			'#type' => 'date_popup',
			'#title' => t('Start'),
			'#date_format' => 'M d, Y',
			'#default_value' => !empty($start_date) ? date('Y-m-d h:i:s', $start_date) : NULL,
			'#required' => TRUE,
	);
	$form['end_date'] = array(
			'#type' => 'date_popup',
			'#title' => t('End'),
			'#date_format' => 'M d, Y',
			'#default_value' => !empty($end_date) ? date('Y-m-d h:i:s', $end_date) : NULL,
			'#required' => TRUE,
	);
	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Submit'),
	);

	if (!empty($start_date) && !empty($end_date)) {
		$data = cgsi_reports_membership_weekly_generate($start_date, $end_date);

		$theme_vars = array();
		$theme_vars['rows'] = $data['rows'];
		$theme_vars['header'] = $data['headers'];

		$form['report'] = array(
				'#type' => 'markup',
				'#markup' => theme('table', $theme_vars),
		);
		$form['report_export'] = array(
				'#type' => 'markup',
				'#markup' => theme('item_list', array('items' => array(l(t('Download CSV')
						, 'admin/user/reports/membership-weekly/csv'
						, array('query' => array('start_date' => $start_date, 'end_date' => $end_date))
				),
				)
				)
				)
		);
	}

	return $form;
}

function cgsi_reports_membership_weekly_csv() {
	$start_date = check_plain($_GET['start_date']);
	$end_date = check_plain($_GET['end_date']);
	if ((!$start_date && !$end_date) || ($start_date > $end_date)) {
		drupal_goto('admin/user/reports/membership-weekly');
	}

	$data = cgsi_reports_membership_weekly_generate($start_date, $end_date);
	cgsi_reports_table_export('membership-activity-' . date('Y-m-d', $start_date) . '-to-' . date('Y-m-d', $end_date) . '.csv', $data['headers'], $data['rows']);
}

/**
 * Validation callback for cgsi_reports_membership_weekly form.
 */
function cgsi_reports_membership_weekly_validate($form, &$form_state) {
	$start_date = strtotime($form_state['values']['start_date']);
	$end_date = strtotime($form_state['values']['end_date']);
	if (!$start_date) {
		form_set_error('start_date', t('Please choose a valid start date.'));
	}
	if (!$end_date) {
		form_set_error('end_date', t('Please choose a valid end date.'));
	}
	if ($end_date <= $start_date) {
		form_set_error('end_date', t('Please choose an end date that occurs after the start date.'));
	}
}

/**
 * Submit handler for function cgsi_reports_membership_weekly form.
 */
function cgsi_reports_membership_weekly_submit($form, &$form_state) {
	$start_date = strtotime($form_state['values']['start_date']);
	$end_date = strtotime($form_state['values']['end_date']);
	drupal_goto("admin/user/reports/membership-weekly", array('query'=>array('start_date' => $start_date, 'end_date' => $end_date)));
}

/**
 * Generate a membership report for a given date range.
 *
 * @param $start_date
 *   Timestamp representing the date you would like reporting to start.
 * @param $end_date
 *   Timestamp representing the date you would like reporting to end.
 *
 * @return
 *   An FAPI array containing the formatted report.
 */
function cgsi_reports_membership_weekly_generate($start_date, $end_date) {
	$membership_products = _cgsi_reports_membership_products();
	$membership_terms = array_flip(_cgsi_signup_get_terms_array());
	$membership_levels = array_flip(_cgsi_signup_get_levels_array());

	// Donation information for date range. Done this way rather than hitting the
	// DB for every account.
	$donations = array();
	$results = db_query("SELECT uid, donation_type, amount FROM {cgsi_donations_history} WHERE created > {$start_date} AND created < {$end_date}");
	foreach ($results as $row ) {
		$donations[$row->uid][$row->donation_type] += $row->amount;
	}

	// Renewing users for date range.
	$results = db_query("SELECT DISTINCT(uid) AS uid FROM {uc_roles_history} WHERE activity = 'renew' AND created > {$start_date} AND created < {$end_date} ORDER BY created");
	$renewals = array();
	$renewal_totals = array();
	foreach ($results as $row) {
		// Account object.
		$account = user_load($row->uid);
		// Membership price based on term/level.
		$node = $membership_products['cgsi_signup_cgsi_signup_us_' . $membership_terms[$account->profile_membership_term] . '_' . $membership_levels[$account->profile_membership_level] . '_nid'];
		$renewals[$account->uid] = _cgsi_reports_process_account_for_weekly_report($account, $node, $donations, $renewal_totals);
	}

	$arr = array(array('data' => t('<strong>Renewal Memberships Count: @count</strong>', array('@count' => count($renewals))), 'colspan' => 13));
	array_unshift($renewals, $arr);

	$renewals['renewal_totals'] = array(
			array('data' => t('<strong>Renwal Totals:</strong>'), 'colspan' => 5),
			'<strong>$' . money_format('%n', $renewal_totals['membership_price']) . '</strong>',
			'<strong>$' . money_format('%n', $renewal_totals['library_donation']) . '</strong>',
			'<strong>$' . money_format('%n', $renewal_totals['total_amount']) . '</strong>',
			'',
			'<strong>$' . money_format('%n', $renewal_totals['sponsor_donation']) . '</strong>',
			'<strong>$' . money_format('%n', $renewal_totals['postage']) . '</strong>',
			'',
	);

	$headers = array(
			t('#'),
			t('First'),
			t('Last'),
			t('Type'),
			t('Term'),
			t('Membership Price'),
			t('Lib. Donation'),
			t('Total Amount Paid'),
			t('CR CD'),
			t('Sponsor Donation'),
			t('1st class postage'),
			t('Remarks'),
	);

	// New users for date range.
	$results = db_query("SELECT uid FROM {uc_roles_history} WHERE activity = 'new' AND created > {$start_date} AND created < {$end_date} ORDER BY created");
	$new = array();
	$new_totals = array();
	foreach ($results as $row ) {
		// Account object.
		$account = user_load($row->uid);
		// Membership price based on term/level.
		$node = $membership_products['cgsi_signup_cgsi_signup_us_' . $membership_terms[$account->profile_membership_term] . '_' . $membership_levels[$account->profile_membership_level] . '_nid'];
		$new[$account->uid] = _cgsi_reports_process_account_for_weekly_report($account, $node, $donations, $new_totals);
	}

	// Add a count row.
	$arr = array(array('data' => t('<strong>New Memberships Count: @count</strong>', array('@count' => count($new))), 'colspan' => 13));
	array_unshift($new, $arr);

	$new['new_totals'] = array(
			array('data' => t('<strong>New Member Totals:</strong>'), 'colspan' => 5),
			'<strong>$' . money_format('%n', $new_totals['membership_price']) . '</strong>',
			'<strong>$' . money_format('%n', $new_totals['library_donation']) . '</strong>',
			'<strong>$' . money_format('%n', $new_totals['total_amount']) . '</strong>',
			'',
			'<strong>$' . money_format('%n', $new_totals['sponsor_donation']) . '</strong>',
			'<strong>$' . money_format('%n', $new_totals['postage']) . '</strong>',
			'',
	);

	// Cancelations.
	$results = db_query("SELECT uid FROM {cgsi_status_history} WHERE (status='inactive' OR status = 'inactive_cancel' OR status = 'inactive_death') AND modified > {$start_date} AND modified < {$end_date} ORDER BY status, modified");
	$cancel = array();
	$cancel_totals = array();
	foreach ($results as $row ) {
		// Account object.
		$account = user_load($row->uid);
		// Membership price based on term/level.
		$node = $membership_products['cgsi_signup_cgsi_signup_us_' . $membership_terms[$account->profile_membership_term] . '_' . $membership_levels[$account->profile_membership_level] . '_nid'];
		//$cancel[$account->uid] = _cgsi_reports_process_account_for_weekly_report($account, $node, $donations, $cancel_totals);
		$cancel[$account->uid] = array(
				l($account->profile_member_number, 'user/' . $account->uid),
				$account->profile_first_name,
				$account->profile_last_name,
				$account->cgsi_status,
				array('colspan' => 9),
		);
	}

	// Add a count row.
	$arr = array(array('data' => t('<strong>New Cancelations: @count</strong>', array('@count' => count($cancel))), 'colspan' => 13));
	array_unshift($cancel, $arr);

	// Expirations
	$results = db_query("SELECT uid FROM {uc_roles_history} WHERE activity = 'revoke' AND created > {$start_date} AND created < {$end_date} ORDER BY created");
	$revoked = array();
	$revoked_totals = array();
	foreach ($results as $row ) {
		// Account object.
		$account = user_load($row->uid);
		$revoked[$account->uid] = array(
				l($account->profile_member_number, 'user/' . $account->uid),
				$account->profile_first_name,
				$account->profile_last_name,
				t('expired'),
				array('colspan' => 9),
		);
	}

	$arr = array(array('data' => t('<strong>Expired Memberships Count: @count</strong>', array('@count' => count($revoked))), 'colspan' => 13));
	array_unshift($revoked, $arr);

	// Totals.
	$totals_rows = array();
	$totals_rows['totals_check'] = array(
			array('data' => t('<strong>Check Totals</strong>'), 'colspan' => 7),
			array('data' => '$' . money_format('%n', $renewal_totals['total_check'] + $new_totals['total_check']), 'colspan' => 5),
	);
	$totals_rows['totals_cc'] = array(
			array('data' => t('<strong>Credit Card Totals</strong>'), 'colspan' => 7),
			array('data' => '$' . money_format('%n', $renewal_totals['total_cc'] + $new_totals['total_cc']), 'colspan' => 5),
	);
	$totals_rows['totals_total'] = array(
			array('data' => t('<strong>Grand Totals</strong>'), 'colspan' => 5),
			'$' . money_format('%n', $renewal_totals['membership_price'] + $new_totals['membership_price']),
			'$' . money_format('%n', $renewal_totals['library_donation'] + $new_totals['library_donation']),
			'$' . money_format('%n', $renewal_totals['total_amount'] + $new_totals['total_amount']),
			'',
			'$' . money_format('%n', $renewal_totals['sponsor_donation'] + $new_totals['sponsor_donation']),
			'$' . money_format('%n', $renewal_totals['postage'] + $new_totals['postage']),
			'',
	);

	$rows = array_merge($renewals, $new);
	$rows = array_merge($rows, $cancel);
	$rows = array_merge($rows, $revoked);
	$rows = array_merge($rows, $totals_rows);

	return array('headers' => $headers, 'rows' => $rows);
}

/**
 * Extract information from the supplied user and node objects and prepare it
 * for use in the membership activity report.
 *
 * @param $account
 *   User object representing a member.
 * @param $node
 *   Node object representing the product that matches the term/level $account.
 * @param $dontations
 *   Array containing information about dontations made by $account.
 * @param $totals
 *   Array which stores totals for numeber of members, donations, and other
 *   reported costs. The function will update this array as necessary.
 *
 * @return
 *   An associative array suitable for use as a row in theme_table().
 */
function _cgsi_reports_process_account_for_weekly_report($account, $node, $donations, &$totals) {
	$years = str_replace(' year', '', $account->profile_membership_term);
	$years = (int) $years;

	// First class postage is $10/yr.
	$postage = 0;
	if ($account->profile_class_one_postage != 0) {
		$totals['postage'] += 10 * $years;
		$postage = 10 * $years;
	}

	$total = $node->sell_price + $donations[$account->uid]['Library donation'] + $postage;

	$totals['membership_price'] += ($node->sell_price + $postage);
	$totals['library_donation'] += $donations[$account->uid]['Library donation'];
	$totals['total_amount'] += $total;
	if ($account->profile_payed_by_cc == 1) {
		$totals['total_cc'] += $total;
	}
	else {
		$totals['total_check'] += $total;
	}

	// Calculate sponsor donation if any.
	if ($account->profile_membership_level == 'Sponsor') {
		$years = $account->profile_membership_term;
		if ($years > 2) {
			$donations[$account->uid]['Sponsor donation'] = ceil(15 * $years);
		}
		else {
			$donations[$account->uid]['Sponsor donation'] = ceil(20 * $years);
		}
	}
	$totals['sponsor_donation'] += $donations[$account->uid]['Sponsor donation'];

	return array(
			l($account->profile_member_number, 'user/' . $account->uid),
			$account->profile_first_name,
			$account->profile_last_name,
			$account->profile_membership_level,
			$account->profile_membership_term,
			'$' . money_format('%n', ($node->sell_price + $postage)),
			(($donations[$account->uid]['Library donation']) ? '$' . money_format('%n', $donations[$account->uid]['Library donation']) : ''),
			(($total) ? '$' . money_format('%n', $total) : ''),
			(($account->profile_payed_by_cc == 1) ? 'y' : ''),
			(($donations[$account->uid]['Sponsor donation']) ? '$' . money_format('%n', $donations[$account->uid]['Sponsor donation']) : ''),
			(($postage > 0)) ? '$' . money_format('%n', $postage) : '',
			$account->profile_remarks,  // Remarks?
	);
}

/**
 * Load all the membership product nodes.
 */
function _cgsi_reports_membership_products() {
	static $membership_products;
	if (!isset($membership_products)) {
		$membership_products = array();
		$product_nids = _cgsi_signup_get_variable_names();
		// Remove the last one it is the donation product, and not needed here.
		array_pop($product_nids);
		foreach ($product_nids as $var_name => $product) {
			$nid = variable_get('cgsi_signup_' . $var_name . '_nid', FALSE);
			$node = node_load($nid);
			$membership_products['cgsi_signup_' . $var_name . '_nid'] = $node;
		}
	}
	return $membership_products;
}

/**
 * Query database for profile information for a specific user that is helpful
 * when generating reports.
 *
 * @param $uid
 *   User ID of the user to gather information about.
 * @return
 *   Associative array of profile field values keyed by profile field machine
 *   readable name.
 */
function _cgsi_reports_profile_field($uid) {
	// 6  = State
	// 14 = Membership Level
	// 28 = Membership Term
	// 29 = Source
	$results = db_query("SELECT pv.value, pf.name FROM {profile_value} pv INNER JOIN {profile_field} pf ON pf.fid = pv.fid WHERE pv.fid IN(6, 14, 28, 29) AND pv.uid = {$uid}");
	$fields = array();
	foreach ($results as $row) {
		$fields[$row->name] = $row->value;
	}
	return $fields;
}
