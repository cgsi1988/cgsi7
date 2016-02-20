<?php
/**
 * Filter handler for cgsi_status field.
 */
class cgsi_status_views_handler_filter extends views_handler_filter_many_to_one {
	function get_value_options() {
		$this->value_options = _cgsi_status_status_array();
	}
}
