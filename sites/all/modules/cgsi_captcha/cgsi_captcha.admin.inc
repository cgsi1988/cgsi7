<?php
/**
 * @file
 */

/**
 * Form Builder; Generate the form for use on admin/settings/cgsi_captcha
 */
function cgsi_captcha_admin_settings() {
	// Include the captcha.admin.inc file so we can use some functions from it.
	module_load_include('inc', 'captcha', 'captcha.admin');
	$form = array();
	$form['cgsi_captcha_help'] = array(
			'#type' => 'markup',
			'#value' => '<p>' . t('The CGSI Captcha module allows you to require visitors to complete a captcha form before they are allowed to perform filter operations on a view.') . '</p>',
	);

	$views = views_get_all_views();
	$options = array();
	foreach ($views as $view_name => $view) {
		$options[$view_name] = array();
		foreach ($view->display as $display_name => $display) {
			$options[$view_name][$view_name . '-' . $display_name] = $display_name;
		}
	}

	$form['cgsi_captcha_views'] = array(
			'#type' => 'select',
			'#title' => t('Views'),
			'#options' => $options,
			'#multiple' => TRUE,
			'#default_value' => variable_get('cgsi_captcha_views', FALSE),
	);

	$form['cgsi_captcha_captcha_type'] = array(
			'#type' => 'select',
			'#title' => t('Type of captcha to use'),
			'#options' => _captcha_available_challenge_types(),
			'#default_value' => variable_get('cgsi_captcha_captcha_type', FALSE),
	);
	return system_settings_form($form);
}