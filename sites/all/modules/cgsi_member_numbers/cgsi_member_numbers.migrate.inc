<?php
/**
 * @file
 * Implementation of migrate.module hooks.
 *
 * Allow translation of a member number into a valid {users}.uid
 * during import.
 */

function cgsi_member_numbers_migrate_fields_node($type) {
	return array(
			'cgsi_member_number' => t('Node: Convert Member Number to Author UID'),
	);
}

function cgsi_member_numbers_migrate_prepare_node(&$node, $tblinfo, $row) {
	$errors = array();
	//dsm($node); dsm($tblinfo); dsm($row);
	if (isset($tblinfo->fields['cgsi_member_number'])) {
		$member_number = $row->{$tblinfo->fields['cgsi_member_number']['srcfield']};
		$member_number_default = $tblinfo->fields['cgsi_member_number']['default_value'];
		// Attempt to look up the {user}.uid based on the supplied member number.
		$uid = cgsi_member_numbers_get_uid($member_number);
		if ($uid === FALSE) {
			$errors[] = array(
					'sourceid' => 'cgsi_member_number',
					'level' => MIGRATE_MESSAGE_WARNING,
					'message' => $member_number . ' is not a valid member number.',
			);
		}
		else {
			// And update the node that is about to be created accordingly.
			$node->uid = $uid ? $uid : $member_number_default;
		}
	}

	return $errors;
}
