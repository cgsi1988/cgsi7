<?php
/**
 * @file
 * Admin UI and functions.
 */

/**
 * Form Builder; Simple form for generating a new coupon code.
 */
function cgsi_coupons_form() {
	$form = array();
	$form['coupon_help'] = array(
			'#value' => 'This form can be used to generate a new coupon code for the supplied value. The coupon generated can only be used once and will expire when the value of the coupon is used up.',
	);
	$form['coupon_value'] = array(
			'#type' => 'textfield',
			'#title' => t('Value'),
			'#required' => TRUE,
			'#size' => 10,
			'#field_prefix' => '$',
	);
	$form['coupon_email'] = array(
			'#type' => 'textfield',
			'#title' => t('E-mail address of the person you would like to notify about this coupon.'),
			'#description' => t('The email address above will recieve an e-mail with the new coupon code immediatly after the code is created.'),
	);
	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Generate coupon code'),
	);
	return $form;
}

/**
 * Validation callback for cgsi_coupons_form().
 */
function cgsi_coupons_form_validate($form, &$form_state) {
	if (!is_numeric($form_state['values']['coupon_value'])) {
		form_set_error('coupon_value', t('Coupon value must be a numeric value.'));
	}

	if (isset($form_state['values']['coupon_email']) && !valid_email_address($form_state['values']['coupon_email'])) {
		form_set_error('coupon_email', t('%email is not a valid e-mail address.', array('%email' => $form_state['values']['coupon_email'])));
	}
}

/**
 * Submit handler for cgsi_coupons_form().
 */
function cgsi_coupons_form_submit($form, &$form_state) {
	$form_state['values']['coupon_value'] = intval($form_state['values']['coupon_value']);
	// Set a bunch of default values for the uc_coupon.module coupon and add it.
	$code = strtoupper(user_password());
	$valid_from = time();
	// 5 years
	$valid_until = $valid_from + (60 * 60 * 24 * 365 * 5);
	$data = array();

	$id = db_insert('uc_coupons')
	->fields(array(
			'name' => 'CGSI-GIFT-MEMBERSHIP-' . $form_state['values']['coupon_value']
			, 'code' => $code
			, 'value' => $form_state['values']['coupon_value']
			, 'type' => 'price'
			, 'status' => 1
			, 'valid_until' => $valid_until
			, 'valid_from' => $valid_from
			, 'max_uses' => 0
			, 'minimum_order' => 0
			, 'data' => serialize($data)
			, 'created' => time()
	))
	->execute();
	drupal_set_message(t('New coupon code generated. !code', array('!code' => $code)));
	drupal_set_message(t('This coupon is worth $%value and must be communicated to the customer who purchased the coupon.', array('%value' => $form_state['values']['coupon_value'])));

	// Optionally send an e-mail notification about the new coupon.
	if (isset($form_state['values']['coupon_email'])) {
		drupal_mail('cgsi_coupons', 'cgsi_coupons', $form_state['values']['coupon_email'], language_default(), array('coupon_code' => $code));
		drupal_set_message(t('E-mail sent to %mail. The new coupon code is %coupon_code', array('%mail' => $form_state['values']['coupon_email'], '%coupon_code' => $code)));
	}

	drupal_set_message(l('View all coupons', 'admin/store/coupons'));
}

/**
 * Callback function for drupal_mail to build the message body of the coupon
 * notification e-amil.
 */
function cgsi_coupons_mail($key, &$message, $params) {
	$text = variable_get('cgsi_coupons_mail_text', NULL);
	$text = str_replace('[token-coupon]', $params['coupon_code'], $text);
	// Blind copy a couple of people.
	// @todo: make this configurable.
	$message['headers']['Bcc'] = 'store@cgsi.org, membership@cgsi.org';
	$message['subject'] = t('CGSI Gift Certificate');
	$message['body'][] = $text;
}

/**
 * Form Builder; Settings form.
 */
function cgsi_coupons_settings() {
	$form = array();
	$form['cgsi_coupons_mail_text'] = array(
			'#type' => 'textarea',
			'#title' => t('Email copy - sent out when a new coupon code is generated.'),
			'#rows' => 18,
			'#default_value' => variable_get('cgsi_coupons_mail_text', NULL),
			'#description' => t('The text [token-coupon] will be replaced with the actual coupon code when sending the e-mail.'),
	);
	return system_settings_form($form);
}
