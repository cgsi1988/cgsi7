<?php
/**
 * @file
 */

/**
 * Callback function for admin/settings/cgsi_signup.
 */
function cgsi_signup_settings() {
	$vars = _cgsi_signup_get_variable_names();

	$form = array();
	$form['cgsi_signup'] = array(
			'#type' => 'item',
			'#markup' => t('Choose a product from the store to represent each membership option below. The products should each have attributes for Individual, Family, and Sponsor pricing.'),
			'#prefix' => '<p>',
			'#suffix' => '</p>',
	);

	foreach ($vars as $key => $value) {
		$var_name = 'cgsi_signup_' . $key . '_nid';
		$form[$var_name] = array(
				'#type' => 'select',
				'#title' => t($value),
				'#options' => _cgsi_signup_get_product_nids(),
				'#default_value' => variable_get($var_name, NULL),
		);
	}

	return system_settings_form($form);
}

function _cgsi_signup_get_product_nids() {
	static $cgsi_product_nids = array();

	if (count($cgsi_product_nids)) {
		return $cgsi_product_nids;
	}
	else {
		$results = db_query('SELECT DISTINCT (n.nid), n.title FROM {node} n INNER JOIN {taxonomy_index} tn ON tn.nid=n.nid WHERE tn.tid =20 AND n.status =1');
		$opts = array('' => '(Choose one ...)');
		foreach ($results as $product){
			$opts[$product->nid] = $product->title;
		}
		$cgsi_product_nids = $opts;
		return $opts;
	}
}

/**
 * Form Builder; Resend a welcome message to a user.
 *
 * @param $account
 *   The user object as passed in by the user_load menu loader.
 */
function cgsi_signup_resend($form, &$form_state, $form_id = '') {
	$account = $form_state['build_info']['args'][0];
	drupal_set_title(t('Resend Messages: @username', array('@username' => $account->name)));

	$form = array();
	$form['#account'] = $account;
	$messages = _cgsi_signup_resend_messages();
	$form['help'] = array(
			'#type' => 'item',
			'#markup' => t('Use the form below to re-send a welcome or renewal message to %name', array('%name' => $account->name)),
	);
	$form['message'] = array(
			'#type' => 'select',
			'#title' => t('Choose the message you would like to resend'),
			'#options' => $messages,
			'#required' => TRUE,
	);
        $form['orderID'] = array(
                        '#type' => 'hidden',
                        '#value' => 1,
        );
	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Resend'),
	);
	return $form;
}

/**
 * Form Builder; Submit callback for cgsi_signup_resend().
 */
function cgsi_signup_resend_submit($form, &$form_state) {
	$event_name = $form_state['values']['message'];
	$account = $form['#account'];
	$user_id = $account->uid;

	// Find the user's most recent order with a membership
	$query = db_select('uc_orders', 'o');
	$query->leftJoin('uc_order_products', 'op', 'op.order_id = o.order_id ');
	$query->leftJoin('uc_roles_products', 'p', 'op.nid = p.nid');
	$query->leftJoin('uc_roles_expirations', 'e', 'e.rid = p.rid AND e.uid = o.uid');
	$query->orderBy('o.order_id', 'DESC');
	$query->extend('PagerDefault')->limit(1);
	$query->fields('o', array('order_id'));
	$query->fields('e', array('reid'));
	$query->condition('o.uid', $user_id);

	$order_role_expiration = $query->execute()->fetchObject();

	$order_id = $order_role_expiration->order_id;
	$uc_order = db_query("SELECT * FROM {uc_orders} WHERE order_id = :order_id", array(':order_id' => $order_id))->fetchObject();
	$role_expiration = db_query("SELECT * FROM {uc_roles_expirations} WHERE reid = :reid", array(':reid' => $order_role_expiration->reid))->fetchObject();

	rules_invoke_event($event_name, $uc_order, $role_expiration);
}

/**
 * Get a list of all messages that can be re-sent. This list is currently
 * hard coded.
 *
 * @return
 *   An associative array, key is the value of {ca_predicates}.pid of the mail
 *   that can be sent and value is the title to display to the admin when
 *   choosing a message to resend.
 */
function _cgsi_signup_resend_messages() {
	return array(
	'uc_roles_notify_grant' => t('New Member (donation message will be sent if applicable)'),
	'uc_roles_notify_renew' => t('Membership Renewal (donation message will be sent if applicable)'),
	);
}
