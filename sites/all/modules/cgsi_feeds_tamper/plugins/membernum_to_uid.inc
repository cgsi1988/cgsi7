<?php

/**
 * @file
 * Set field to default value.
 */

$plugin = array(
		'form'     => 'cgsi_feeds_tamper_membernum_to_uid_form',
		'callback' => 'cgsi_feeds_tamper_membernum_to_uid_callback',
		'name'     => 'Convert member number to User ID',
		'multi'    => 'direct',
		'category' => 'Other',
);

function cgsi_feeds_tamper_membernum_to_uid_form($importer, $element_key, $settings) {
	$form = array();

	$form['description'] = array(
			'#type' => 'markup',
			'#markup' => t('If the given input is a valid member number, the member\'s user ID will be returned.')
	);
	return $form;
}

function cgsi_feeds_tamper_membernum_to_uid_callback($source, $item_key, $element_key, &$field, $settings) {
	if ($uid = cgsi_member_numbers_get_uid($field)) {
		$field = $uid;
	}
	else {
		$field = 0;
	}
}
