<?php
/**
 * @file
 * Definition of cgsi_status_views_handler_filter.
 */

/**
 * Filter handler which uses list-fields as options.
 *
 * @ingroup views_filter_handlers
 */

class views_handler_filter_status extends views_handler_filter_many_to_one {
	function get_value_options() {
		$this->value_options = _cgsi_status_status_array();
	}
}