<?php

/**
 * Implementation of hook_node_info().
 */
function cgsi_surnames_node_info() {
	$items = array(
			'surname' => array(
					'name' => t('Surname'),
					'module' => 'features',
					'description' => t('Add a new Surname to the CGSI members surname database.'),
					'has_title' => '1',
					'title_label' => t('Surname'),
					'has_body' => '0',
					'body_label' => '',
					'min_word_count' => '0',
					'help' => t('<p>CGSI has been collecting member surnames for years, along with data on the village, town, or district of origin. By using this resource, you may be able to locate long-lost relatives locally or in their ancestral area. Submit as many names as you wish. Update as new names are found or if you find corrections are needed.</p>

							<p><strong>Diacritical marks:</strong> Please enter your surnames and European locations without diacritical marks. Due to the difficulty some computers have in viewing the diacriticals and the fact that they would not permit a “search” function to operate properly, diacriticals are not able to be used.</p>

							<p><strong>CGSI Disclaimer:</strong> By entering your surnames into this database, you are granting access to your contact information (home address and email address) to fellow members whose own search results in a hit on one or more of your submitted surname records. Sharing contact information with fellow members is necessary to determine if there is any relationship between your respective surname records.  If you want to display only your email address and do NOT want to display your home address to other members, go to your <a href="../../user/edit/member-information">My Profile</a> page and UN-CHECK the box that says "Display my home address to other members whose own search results in a hit on one of our common Surnames or City/Village of Origin names."</p>'),
			),
	);
	return $items;
}

/**
 * Implementation of hook_views_api().
 */
function cgsi_surnames_views_api() {
	return array(
			'api' => '2',
	);
}
