<?php

/**
 * Implementation of hook_views_default_views().
 */
function cgsi_surnames_views_default_views() {
	$views = array();

	// Exported view: Surnames
	$view = new view;
	$view->name = 'Surnames';
	$view->description = 'Display surnames';
	$view->tag = '';
	$view->view_php = '';
	$view->base_table = 'node';
	$view->is_cacheable = FALSE;
	$view->api_version = 2;
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
	$handler = $view->new_display('default', 'Defaults', 'default');
	$handler->override_option('fields', array(
			'title' => array(
					'label' => 'Surname',
					'alter' => array(
							'alter_text' => 0,
							'text' => '',
							'make_link' => 0,
							'path' => '',
							'link_class' => '',
							'alt' => '',
							'prefix' => '',
							'suffix' => '',
							'help' => '',
							'trim' => 0,
							'max_length' => '',
							'word_boundary' => 1,
							'ellipsis' => 1,
							'strip_tags' => 0,
							'html' => 0,
					),
					'link_to_node' => 1,
					'exclude' => 0,
					'id' => 'title',
					'table' => 'node',
					'field' => 'title',
					'relationship' => 'none',
			),
			'field_surname_european_city_value' => array(
					'label' => 'European City',
					'alter' => array(
							'alter_text' => 0,
							'text' => '',
							'make_link' => 0,
							'path' => '',
							'link_class' => '',
							'alt' => '',
							'prefix' => '',
							'suffix' => '',
							'help' => '',
							'trim' => 0,
							'max_length' => '',
							'word_boundary' => 1,
							'ellipsis' => 1,
							'strip_tags' => 0,
							'html' => 0,
					),
					'link_to_node' => 0,
					'label_type' => 'widget',
					'format' => 'default',
					'multiple' => array(
							'group' => TRUE,
							'multiple_number' => '',
							'multiple_from' => '',
							'multiple_reversed' => FALSE,
					),
					'exclude' => 0,
					'id' => 'field_surname_european_city_value',
					'table' => 'node_data_field_surname_european_city',
					'field' => 'field_surname_european_city_value',
					'relationship' => 'none',
			),
			'field_surname_european_country_value' => array(
					'label' => 'European Country',
					'alter' => array(
							'alter_text' => 0,
							'text' => '',
							'make_link' => 0,
							'path' => '',
							'link_class' => '',
							'alt' => '',
							'prefix' => '',
							'suffix' => '',
							'help' => '',
							'trim' => 0,
							'max_length' => '',
							'word_boundary' => 1,
							'ellipsis' => 1,
							'strip_tags' => 0,
							'html' => 0,
					),
					'link_to_node' => 0,
					'label_type' => 'widget',
					'format' => 'default',
					'multiple' => array(
							'group' => TRUE,
							'multiple_number' => '',
							'multiple_from' => '',
							'multiple_reversed' => FALSE,
					),
					'exclude' => 0,
					'id' => 'field_surname_european_country_value',
					'table' => 'node_data_field_surname_european_country',
					'field' => 'field_surname_european_country_value',
					'relationship' => 'none',
			),
			'field_surname_immigration_area_value' => array(
					'label' => 'Immigration area',
					'alter' => array(
							'alter_text' => 0,
							'text' => '',
							'make_link' => 0,
							'path' => '',
							'link_class' => '',
							'alt' => '',
							'prefix' => '',
							'suffix' => '',
							'help' => '',
							'trim' => 0,
							'max_length' => '',
							'word_boundary' => 1,
							'ellipsis' => 1,
							'strip_tags' => 0,
							'html' => 0,
					),
					'link_to_node' => 0,
					'label_type' => 'widget',
					'format' => 'default',
					'multiple' => array(
							'group' => TRUE,
							'multiple_number' => '',
							'multiple_from' => '',
							'multiple_reversed' => FALSE,
					),
					'exclude' => 0,
					'id' => 'field_surname_immigration_area_value',
					'table' => 'node_data_field_surname_immigration_area',
					'field' => 'field_surname_immigration_area_value',
					'relationship' => 'none',
			),
			'changed' => array(
					'label' => 'Last Modified',
					'alter' => array(
							'alter_text' => 0,
							'text' => '',
							'make_link' => 0,
							'path' => '',
							'link_class' => '',
							'alt' => '',
							'prefix' => '',
							'suffix' => '',
							'target' => '',
							'help' => '',
							'trim' => 0,
							'max_length' => '',
							'word_boundary' => 1,
							'ellipsis' => 1,
							'strip_tags' => 0,
							'html' => 0,
					),
					'empty' => '',
					'hide_empty' => 0,
					'empty_zero' => 0,
					'date_format' => 'custom',
					'custom_date_format' => 'm/d/Y',
					'exclude' => 0,
					'id' => 'changed',
					'table' => 'node',
					'field' => 'changed',
					'override' => array(
							'button' => 'Override',
					),
					'relationship' => 'none',
			),
			'field_surname_comments_value' => array(
					'label' => 'C',
					'alter' => array(
							'alter_text' => 1,
							'text' => '<strong>C</strong>',
							'make_link' => 0,
							'path' => '',
							'link_class' => '',
							'alt' => '',
							'prefix' => '',
							'suffix' => '',
							'target' => '',
							'help' => '',
							'trim' => 0,
							'max_length' => '',
							'word_boundary' => 1,
							'ellipsis' => 1,
							'strip_tags' => 0,
							'html' => 0,
					),
					'empty' => '',
					'hide_empty' => 1,
					'empty_zero' => 0,
					'link_to_node' => 0,
					'label_type' => 'custom',
					'format' => 'default',
					'multiple' => array(
							'group' => TRUE,
							'multiple_number' => '',
							'multiple_from' => '',
							'multiple_reversed' => FALSE,
					),
					'exclude' => 0,
					'id' => 'field_surname_comments_value',
					'table' => 'node_data_field_surname_comments',
					'field' => 'field_surname_comments_value',
					'override' => array(
							'button' => 'Override',
					),
					'relationship' => 'none',
			),
	));
	$handler->override_option('sorts', array(
			'title' => array(
					'order' => 'ASC',
					'id' => 'title',
					'table' => 'node',
					'field' => 'title',
					'relationship' => 'none',
			),
	));
	$handler->override_option('filters', array(
			'status' => array(
					'operator' => '=',
					'value' => '1',
					'group' => '0',
					'exposed' => FALSE,
					'expose' => array(
							'operator' => FALSE,
							'label' => '',
					),
					'id' => 'status',
					'table' => 'node',
					'field' => 'status',
					'relationship' => 'none',
			),
			'type' => array(
					'operator' => 'in',
					'value' => array(
							'surname' => 'surname',
					),
					'group' => '0',
					'exposed' => FALSE,
					'expose' => array(
							'operator' => FALSE,
							'label' => '',
					),
					'id' => 'type',
					'table' => 'node',
					'field' => 'type',
					'relationship' => 'none',
			),
	));
	$handler->override_option('access', array(
			'type' => 'role',
			'role' => array(
					'4' => 4,
					'7' => 7,
					'5' => 5,
					'8' => 8,
					'6' => 6,
					'3' => 3,
					'9' => 9,
			),
	));
	$handler->override_option('cache', array(
			'type' => 'none',
	));
	$handler->override_option('title', 'Surnames');
	$handler->override_option('style_plugin', 'table');
	$handler->override_option('style_options', array(
			'grouping' => '',
			'override' => 1,
			'sticky' => 0,
			'order' => 'asc',
			'columns' => array(
					'title' => 'title',
					'field_surname_european_city_value' => 'field_surname_european_city_value',
					'field_surname_european_country_value' => 'field_surname_european_country_value',
					'field_surname_immigration_area_value' => 'field_surname_immigration_area_value',
					'changed' => 'changed',
					'field_surname_comments_value' => 'field_surname_comments_value',
			),
			'info' => array(
					'title' => array(
							'sortable' => 1,
							'separator' => '',
					),
					'field_surname_european_city_value' => array(
							'sortable' => 1,
							'separator' => '',
					),
					'field_surname_european_country_value' => array(
							'sortable' => 1,
							'separator' => '',
					),
					'field_surname_immigration_area_value' => array(
							'sortable' => 1,
							'separator' => '',
					),
					'changed' => array(
							'sortable' => 1,
							'separator' => '',
					),
					'field_surname_comments_value' => array(
							'sortable' => 0,
							'separator' => '',
					),
			),
			'default' => '-1',
	));
	$handler = $view->new_display('page', 'My Surnames - Page', 'page_1');
	$handler->override_option('arguments', array(
			'uid_touch' => array(
					'default_action' => 'default',
					'style_plugin' => 'default_summary',
					'style_options' => array(),
					'wildcard' => 'all',
					'wildcard_substitution' => 'All',
					'title' => 'My Surnames: %1',
					'breadcrumb' => '',
					'default_argument_type' => 'user',
					'default_argument' => '',
					'validate_type' => 'php',
					'validate_fail' => 'not found',
					'id' => 'uid_touch',
					'table' => 'node',
					'field' => 'uid_touch',
					'validate_user_argument_type' => 'either',
					'validate_user_roles' => array(
							'2' => 0,
							'4' => 0,
							'7' => 0,
							'5' => 0,
							'8' => 0,
							'6' => 0,
							'3' => 0,
							'9' => 0,
					),
					'override' => array(
							'button' => 'Use default',
					),
					'relationship' => 'none',
					'default_options_div_prefix' => '',
					'default_argument_user' => 0,
					'default_argument_fixed' => '',
					'default_argument_php' => '',
					'validate_argument_node_type' => array(
							'surname' => 0,
							'product' => 0,
							'donation' => 0,
							'church_record' => 0,
							'event' => 0,
							'lending_library_item' => 0,
							'msg_bd_post' => 0,
							'news' => 0,
							'page' => 0,
							'passenger_ship_record' => 0,
							'popup_page' => 0,
							'public_lib_item' => 0,
							'query' => 0,
					),
					'validate_argument_node_access' => 0,
					'validate_argument_nid_type' => 'nid',
					'validate_argument_vocabulary' => array(
							'6' => 0,
							'7' => 0,
							'1' => 0,
							'5' => 0,
							'2' => 0,
							'3' => 0,
							'8' => 0,
							'4' => 0,
					),
					'validate_argument_type' => 'tid',
					'validate_argument_transform' => 0,
					'validate_user_restrict_roles' => 0,
					'validate_argument_php' => 'global $user;
					if ($user->uid == $argument || user_access(\'administer users\')) {
					return TRUE;
}
					return FALSE;',
			),
	));
	$handler->override_option('title', 'My Surnames');
	$handler->override_option('header', 'h3. Surnames you are researching: "add a Surname":node/add/surname

			CGSI has been collecting member surnames for years, along with data on the village, town, or district of origin. By using this resource, you may be able to locate long-lost relatives locally or in their ancestral area. Submit as many names as you wish. Update as new names are found or if you find corrections are needed.

			*Diacritical marks:* Please enter your surnames and European locations without diacritical marks. Due to the difficulty some computers have in viewing the diacriticals and the fact that they would not permit a search function to operate properly, diacriticals are not able to be used.

			*CGSI Disclaimer:* By entering your surnames into this database, you are granting access to your contact information (home address and email address) to fellow members whose own search results in a hit on one or more of your submitted surname records. Sharing contact information with fellow members is necessary to determine if there is any relationship between your respective surname records. If you want to display only your email address and do NOT want to display your home address to other members, go to your "My Profile":user/edit/member-information page and UN-CHECK the box that says "Display my home address to other members whose own search results in a hit on one of our common Surnames or City/Village of Origin names."

			Sort any column by clicking on the column name. Edit individual entries by clicking on that surname.

			The capital "C" in the right hand column indicates you have entered a comment for the associated surname.');
	$handler->override_option('header_format', '4');
	$handler->override_option('header_empty', 1);
	$handler->override_option('empty', 'You have not added any surnames yet. "Add a surname":node/add/surname');
	$handler->override_option('empty_format', '4');
	$handler->override_option('items_per_page', 0);
	$handler->override_option('path', 'user/%/surnames');
	$handler->override_option('menu', array(
			'type' => 'tab',
			'title' => 'My Surnames',
			'description' => '',
			'weight' => '0',
			'name' => 'navigation',
	));
	$handler->override_option('tab_options', array(
			'type' => 'none',
			'title' => '',
			'description' => '',
			'weight' => 0,
	));
	$handler = $view->new_display('page', 'Page - Surname search', 'page_2');
	$handler->override_option('filters', array(
			'status' => array(
					'operator' => '=',
					'value' => '1',
					'group' => '0',
					'exposed' => FALSE,
					'expose' => array(
							'operator' => FALSE,
							'label' => '',
					),
					'id' => 'status',
					'table' => 'node',
					'field' => 'status',
					'relationship' => 'none',
			),
			'type' => array(
					'operator' => 'in',
					'value' => array(
							'surname' => 'surname',
					),
					'group' => '0',
					'exposed' => FALSE,
					'expose' => array(
							'operator' => FALSE,
							'label' => '',
					),
					'id' => 'type',
					'table' => 'node',
					'field' => 'type',
					'relationship' => 'none',
			),
			'title_soundslike' => array(
					'id' => 'title_soundslike',
					'table' => 'node',
					'field' => 'title_soundslike',
					'exposed' => TRUE,
					'expose' => array(
							'use_operator' => 1,
							'operator' => 'title_soundslike_op',
							'identifier' => 'title_soundslike',
							'label' => 'Surname',
							'optional' => 1,
							'remember' => 1,
					),
					'override' => array(
							'button' => 'Use default',
					),
					'relationship' => 'none',
					'operator' => 'starts',
					'value' => '',
					'case' => 0,
			),
			'field_surname_european_city_value' => array(
					'operator' => 'contains',
					'value' => '',
					'group' => '0',
					'exposed' => TRUE,
					'expose' => array(
							'use_operator' => 1,
							'operator' => 'field_surname_european_city_value_op',
							'identifier' => 'field_surname_european_city_value',
							'label' => 'City/Village of Origin',
							'optional' => 1,
							'remember' => 1,
					),
					'case' => 1,
					'id' => 'field_surname_european_city_value',
					'table' => 'node_data_field_surname_european_city',
					'field' => 'field_surname_european_city_value',
					'override' => array(
							'button' => 'Use default',
					),
					'relationship' => 'none',
			),
			'field_surname_european_country_value_many_to_one' => array(
					'operator' => 'or',
					'value' => array(),
					'group' => '0',
					'exposed' => TRUE,
					'expose' => array(
							'use_operator' => 0,
							'operator' => 'field_surname_european_country_value_many_to_one_op',
							'identifier' => 'field_surname_european_country_value_many_to_one',
							'label' => 'European Country',
							'optional' => 1,
							'single' => 1,
							'remember' => 1,
							'reduce' => 0,
					),
					'id' => 'field_surname_european_country_value_many_to_one',
					'table' => 'node_data_field_surname_european_country',
					'field' => 'field_surname_european_country_value_many_to_one',
					'override' => array(
							'button' => 'Use default',
					),
					'relationship' => 'none',
					'reduce_duplicates' => 0,
			),
			'field_surname_immigration_area_value' => array(
					'operator' => 'contains',
					'value' => '',
					'group' => '0',
					'exposed' => TRUE,
					'expose' => array(
							'use_operator' => 1,
							'operator' => 'field_surname_immigration_area_value_op',
							'identifier' => 'field_surname_immigration_area_value',
							'label' => 'Immigration area (US or other)',
							'optional' => 1,
							'remember' => 1,
					),
					'case' => 1,
					'id' => 'field_surname_immigration_area_value',
					'table' => 'node_data_field_surname_immigration_area',
					'field' => 'field_surname_immigration_area_value',
					'override' => array(
							'button' => 'Use default',
					),
					'relationship' => 'none',
			),
	));
	$handler->override_option('title', 'Member Surnames Search');
	$handler->override_option('empty', 'Your search did not return any results. Check the availability of records on the "Introduction page":members/surnames-search.');
	$handler->override_option('empty_format', '4');
	$handler->override_option('items_per_page', 200);
	$handler->override_option('use_pager', '1');
	$handler->override_option('path', 'members/surnames/search');
	$handler->override_option('menu', array(
			'type' => 'none',
			'title' => '',
			'description' => '',
			'weight' => 0,
			'name' => 'navigation',
	));
	$handler->override_option('tab_options', array(
			'type' => 'none',
			'title' => '',
			'description' => '',
			'weight' => 0,
	));
	$handler = $view->new_display('page', 'Page - User surnames', 'page_3');
	$handler->override_option('arguments', array(
			'uid_touch' => array(
					'default_action' => 'not found',
					'style_plugin' => 'default_summary',
					'style_options' => array(),
					'wildcard' => 'all',
					'wildcard_substitution' => 'All',
					'title' => 'Surnames for %1',
					'breadcrumb' => '',
					'default_argument_type' => 'fixed',
					'default_argument' => '',
					'validate_type' => 'user',
					'validate_fail' => 'not found',
					'id' => 'uid_touch',
					'table' => 'node',
					'field' => 'uid_touch',
					'validate_user_argument_type' => 'uid',
					'validate_user_roles' => array(
							'2' => 0,
							'4' => 0,
							'7' => 0,
							'5' => 0,
							'8' => 0,
							'6' => 0,
							'3' => 0,
							'9' => 0,
					),
					'override' => array(
							'button' => 'Use default',
					),
					'relationship' => 'none',
					'default_options_div_prefix' => '',
					'default_argument_user' => 0,
					'default_argument_fixed' => '',
					'default_argument_php' => '',
					'validate_argument_node_type' => array(
							'surname' => 0,
							'product' => 0,
							'donation' => 0,
							'church_record' => 0,
							'event' => 0,
							'lending_library_item' => 0,
							'msg_bd_post' => 0,
							'news' => 0,
							'page' => 0,
							'passenger_ship_record' => 0,
							'popup_page' => 0,
							'public_lib_item' => 0,
							'query' => 0,
					),
					'validate_argument_node_access' => 0,
					'validate_argument_nid_type' => 'nid',
					'validate_argument_vocabulary' => array(
							'6' => 0,
							'7' => 0,
							'1' => 0,
							'5' => 0,
							'2' => 0,
							'3' => 0,
							'8' => 0,
							'4' => 0,
					),
					'validate_argument_type' => 'tid',
					'validate_argument_transform' => 0,
					'validate_user_restrict_roles' => 0,
					'validate_argument_php' => '',
			),
	));
	$handler->override_option('header', '"Back to search results":members/surnames/search');
	$handler->override_option('header_format', '4');
	$handler->override_option('header_empty', 0);
	$handler->override_option('items_per_page', 0);
	$handler->override_option('path', 'members/surnames/search/user');
	$handler->override_option('menu', array(
			'type' => 'none',
			'title' => '',
			'description' => '',
			'weight' => 0,
			'name' => 'navigation',
	));
	$handler->override_option('tab_options', array(
			'type' => 'none',
			'title' => '',
			'description' => '',
			'weight' => 0,
	));

	$views[$view->name] = $view;

	return $views;
}
