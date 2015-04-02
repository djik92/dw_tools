<?php
require_once 'dw_tools.lib.inc';
require_once 'dw_tools.testing.inc';




/**
 * Fonction qui permet de retourner le nodeid courant.
 * Si problème retourne FALSE
 * @return Ambigous <boolean, The>
 */
function _get_current_nodeid(){
	$nodeid = FALSE;
	if (arg(0) == 'node' && is_numeric(arg(1))){
		$nodeid = arg(1);
	}
	return $nodeid; // show me your nid!
}



function djikweb_admin_configuration_form($form, &$form_state) {
	
	$form['varibles'] = array(
			'#type' 			=> 'radios',
			'#title' 			=> t('Variables Display'),
			'#default_value' 	=> 1,
			'#options' 			=> array( 
								0 	=> t('No'), 
								1 	=> t('Yes'),
								),
			'#required' 		=> TRUE,
	);
	
	$form['actions'] = array(
			'#type' => 'submit',
			'#value' => t('Save configuration'),
	);
	
	return $form;
}





function _test_link($ciid = NULL, $item = ''){
  
  if ($ciid != NULL) {
  
    $tree = db_select('commercial_item', 'c');
    $tree->fields('c', array (
        'parent_id',
        'ciid',
        'title'
    ));
    $tree->condition('c.ciid', $ciid, '=');
    $tree = $tree->execute();
  
    while ( $res = $tree->fetchObject() ) {
      $item = empty($item) ? $res->title : $res->title . ' > ' . $item;
      if (isset($res->parent_id)) {
  
        return _test_link($res->parent_id, $item);
      } else {
        return $item;
      }
    }
  }
  return;
}

/**
 * Fonction qui permet de récupérer le contenu du fichier *.info
 * @author djik
 * @param  $module_name
 * @return string
 */
function _get_file_info($module_name){
  $files = drupal_system_listing('/^' . DRUPAL_PHP_FUNCTION_PATTERN . '\.info$/', 'modules', 'name', 0);
  $files = $files[$module_name];
  
  return file_get_contents($files->uri);
}

function djikweb_admin_configuration_form_submit($form, &$form_state) {
	//print_nice($form_state,10);
}




// hook_form implementation
function dw_tools_configuration($form, &$form_state) {

	$form['display_track_1'] = array(
			'#type' 			=> 'radios',
			'#title' 			=> t('Variable Display Tracking'),
			'#default_value' 	=> _get_default_value(variable_get('djikweb_variables')),
			'#options' 			=> array(
					0 	=> t('No'),
					1 	=> t('Yes'),
			),
			'#required' 		=> TRUE,
	);
	
	$form['display_track_2'] = array(
			'#type' 			=> 'radios',
			'#title' 			=> t('Display choice'),
			'#default_value' 	=> _get_default_value(variable_get('djikweb_track_editor')),
			'#options' 			=> array(
					0 	=> t('Text'),
					1 	=> t('Dpm'),
			),
			'#required' 		=> FALSE,
	);

	$form['submit_button'] = array(
			'#type' => 'submit',
			'#value' => t('Check'),
	);

	return $form;
}


function dw_tools_configuration_submit($form, &$form_state) {

	if($form_state['values']['display_track_1'] == '1'){
		variable_set('djikweb_variables','1');
	} else {
		variable_set('djikweb_variables','0');
	}
	
	if($form_state['values']['display_track_2'] == '1'){
		variable_set('djikweb_track_editor','1');
	} else {
		variable_set('djikweb_track_editor','0');
	}
}




