<?php 

/**
 * Implementation of hook_drush_command().
 */
function dw_tools_drush_command() {
	$items = array();

	$items['djiktest'] = array(
			'description' 		=> "Makes a delicious sandwich.",
			'arguments' 		=> array(
					'filling' 		=> 'The type of the sandwich (turkey, cheese, etc.)',
			),
			'options' 			=> array(
					'spreads' 		=> 'Comma delimited list of spreads (e.g. mayonnaise, mustard)',
			),
			'examples' 			=> array(
					'drush make-me-a-sandwich turkey --spreads=ketchup,mustard',
			),
			'aliases' 			=> array('mmas'),
			'bootstrap' 		=> DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
	);

	return $items;
}


/**
 * Implementation of hook_drush_help().
 */
function dw_tools_drush_help() {
	switch ($section) {
		case 'drush:djiktest':
			return dt("This command will make you a delicious sandwich, just how you like it.");
	}
}

function drush_dw_tools_djiktest() {
	return 'djiktest';
}
