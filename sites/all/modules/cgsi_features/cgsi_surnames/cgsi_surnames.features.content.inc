<?php

/**
 * Implementation of hook_content_default_fields().
 */
function cgsi_surnames_content_default_fields() {
	$fields = array();

	// Exported field: field_surname_comments
	$fields['surname-field_surname_comments'] = array(
			'field_name' => 'field_surname_comments',
			'type_name' => 'surname',
			'display_settings' => array(
					'label' => array(
							'format' => 'above',
							'exclude' => 0,
					),
					'teaser' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'full' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'4' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'2' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'3' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'token' => array(
							'format' => 'default',
							'exclude' => 0,
					),
			),
			'widget_active' => '1',
			'type' => 'text',
			'required' => '0',
			'multiple' => '0',
			'module' => 'text',
			'active' => '1',
			'text_processing' => '0',
			'max_length' => '',
			'allowed_values' => '',
			'allowed_values_php' => '',
			'widget' => array(
					'rows' => '5',
					'size' => 60,
					'default_value' => array(
							'0' => array(
									'value' => '',
									'_error_element' => 'default_value_widget][field_surname_comments][0][value',
							),
					),
					'default_value_php' => NULL,
					'label' => 'Comments',
					'weight' => 0,
					'description' => 'Optional extra comments.',
					'type' => 'text_textarea',
					'module' => 'text',
			),
	);

	// Exported field: field_surname_european_city
	$fields['surname-field_surname_european_city'] = array(
			'field_name' => 'field_surname_european_city',
			'type_name' => 'surname',
			'display_settings' => array(
					'weight' => '-3',
					'parent' => '',
					'label' => array(
							'format' => 'inline',
					),
					'teaser' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'full' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'4' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'2' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'3' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'token' => array(
							'format' => 'default',
							'exclude' => 0,
					),
			),
			'widget_active' => '1',
			'type' => 'text',
			'required' => '0',
			'multiple' => '0',
			'module' => 'text',
			'active' => '1',
			'text_processing' => '0',
			'max_length' => '255',
			'allowed_values' => '',
			'allowed_values_php' => '',
			'widget' => array(
					'rows' => 5,
					'size' => '60',
					'default_value' => array(
							'0' => array(
									'value' => '',
									'_error_element' => 'default_value_widget][field_surname_european_city][0][value',
							),
					),
					'default_value_php' => NULL,
					'label' => 'City/Village of Origin',
					'weight' => '-3',
					'description' => '',
					'type' => 'text_textfield',
					'module' => 'text',
			),
	);

	// Exported field: field_surname_european_country
	$fields['surname-field_surname_european_country'] = array(
			'field_name' => 'field_surname_european_country',
			'type_name' => 'surname',
			'display_settings' => array(
					'weight' => '-2',
					'parent' => '',
					'label' => array(
							'format' => 'inline',
					),
					'teaser' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'full' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'4' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'2' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'3' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'token' => array(
							'format' => 'default',
							'exclude' => 0,
					),
			),
			'widget_active' => '1',
			'type' => 'text',
			'required' => '0',
			'multiple' => '0',
			'module' => 'text',
			'active' => '1',
			'text_processing' => '0',
			'max_length' => '',
			'allowed_values' => 'Unknown
			Austria
			Bohemia
			Bosnia & Herzegovina
			Carpathian Ruthenia
			Croatia (Hrvatska)
			Czech Republic
			Czechoslovakia
			Galicia
			German Rep
			Hungary
			Moravia
			Poland
			Prussia
			Romania
			Russia
			Silesia
			Slovakia
			Slovenia
			Ukraine
			USSR
			Yugoslavia',
			'allowed_values_php' => '',
			'widget' => array(
					'default_value' => array(
							'0' => array(
									'value' => '',
							),
					),
					'default_value_php' => NULL,
					'label' => 'European Country',
					'weight' => '-2',
					'description' => '',
					'type' => 'optionwidgets_select',
					'module' => 'optionwidgets',
			),
	);

	// Exported field: field_surname_immigration_area
	$fields['surname-field_surname_immigration_area'] = array(
			'field_name' => 'field_surname_immigration_area',
			'type_name' => 'surname',
			'display_settings' => array(
					'weight' => '-1',
					'parent' => '',
					'label' => array(
							'format' => 'inline',
					),
					'teaser' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'full' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'4' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'2' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'3' => array(
							'format' => 'default',
							'exclude' => 0,
					),
					'token' => array(
							'format' => 'default',
							'exclude' => 0,
					),
			),
			'widget_active' => '1',
			'type' => 'text',
			'required' => '0',
			'multiple' => '0',
			'module' => 'text',
			'active' => '1',
			'text_processing' => '0',
			'max_length' => '255',
			'allowed_values' => '',
			'allowed_values_php' => '',
			'widget' => array(
					'rows' => 5,
					'size' => '60',
					'default_value' => array(
							'0' => array(
									'value' => '',
									'_error_element' => 'default_value_widget][field_surname_immigration_area][0][value',
							),
					),
					'default_value_php' => NULL,
					'label' => 'Immigration area (US or other)',
					'weight' => '-1',
					'description' => 'e.g. <em>Spillville, IA, USA</em>',
					'type' => 'text_textfield',
					'module' => 'text',
			),
	);

	// Translatables
	// Included for use with string extractors like potx.
	t('City/Village of Origin');
	t('Comments');
	t('European Country');
	t('Immigration area (US or other)');

	return $fields;
}
