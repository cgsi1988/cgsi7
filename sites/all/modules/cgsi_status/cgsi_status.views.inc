<?php
// $id$

/**
 * @file
 * Views integration for cgsi_status field.
 */

/**
 * Implementation of hook_views_data().
 */
function cgsi_status_views_data() {
	$data['cgsi_status']['table']['group'] = t('CGSI Status');

	$data['cgsi_status']['table']['join'] = array(
			'users' => array(
					'left_field' => 'uid',
					'field' => 'uid',
			),
	);

	$data['cgsi_status']['status'] = array(
			'title' => t('Account Status'),
			'help' => t('Current status for the user account.'),
			'field' => array(
					'handler' => 'views_handler_field',
					'click sortable' => TRUE,
			),
			'filter' => array(
					'handler' => 'cgsi_status_views_handler_filter',
			),
			'argument' => array(
					'handler' => 'views_handler_argument_string',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
	);
	return $data;
}

/**
 * Implement hook_views_handlers().
 */

function cgsi_status_views_handlers() {
	return array(
			'handlers' => array(
					'cgsi_status_views_handler_filter' => array(
							'parent' => 'views_handler_filter_many_to_one',
					),
			),
	);
}