<?php
// $id$

/**
 * @file
 * Views integration for cgsi_donations_history fields.
 */

/**
 * Implementation of hook_views_data().
 */
function cgsi_donations_views_data() {
	$data['cgsi_donations_history']['table']['group'] = t('CGSI Donations');

	$data['cgsi_donations_history']['table']['join'] = array(
			'users' => array(
					'left_field' => 'uid',
					'field' => 'uid',
			),
	);

	$data['cgsi_donations_history']['amount'] = array(
			'title' => t('Donation Amount'),
			'help' => t('Total value of the donation.'),
			'field' => array(
					'handler' => 'views_handler_field',
					'click sortable' => TRUE,
			),
			'filter' => array(
					'handler' => 'views_handler_filter_boolean_operator_string',
			),
			'argument' => array(
					'handler' => 'views_handler_argument_string',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
	);

	$data['cgsi_donations_history']['created'] = array(
			'title' => t('Donation Date'),
			'help' => t('Date the donation was added.'),
			'field' => array(
					'handler' => 'views_handler_field_date',
					'click sortbale' => TRUE,
			),
			'filter' => array(
					'handler' => 'views_handler_filter_date',
			),
			'argumnent' => array(
					'handler' => 'views_hander_argument_date',
			),
			'sort' => array(
					'handler' => 'views_handler_sort_date',
			),
	);

	return $data;
}

