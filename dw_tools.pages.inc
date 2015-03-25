<?php

/**
 * Equivalent a dpm()
 * @param unknown $elem
 * @param number $max_level
 * @param unknown $print_nice_stack
 */
function print_nice($elem,$max_level=2,$print_nice_stack=array()){

	if(is_array($elem) || is_object($elem)){
		if(in_array($elem,$print_nice_stack,true)){
			echo "<font color=red>RECURSION</font>";
			return;
		}
		$print_nice_stack[]=$elem;
		if($max_level<1){
			echo "<font color=red>Niveau max atteint</font>";
			return;
		}
		$max_level--;
		echo "<table border=1 cellspacing=0 cellpadding=3 width=100%>";
		if(is_array($elem)){
			echo '<tr><td colspan=2 style="background-color:#333333;"><strong><font color=white>ARRAY</font></strong></td></tr>';
		}else{
			echo '<tr><td colspan=2 style="background-color:#333333;"><strong>';
			echo '<font color=white>OBJECT Type: '.get_class($elem).'</font></strong></td></tr>';
		}
		$color=0;
		foreach($elem as $k => $v){
			if($max_level%2){
				$rgb=($color++%2)?"#888888":"#BBBBBB";
			}else{
				$rgb=($color++%2)?"#8888BB":"#BBBBFF";
			}
			echo '<tr><td valign="top" style="width:40px;background-color:'.$rgb.';">';
			echo '<strong>'.htmlentities($k)."</strong></td><td>";
			print_nice($v,$max_level,$print_nice_stack);
			echo "</td></tr>";
		}
		echo "</table>";
		return;
	}
	if($elem === null){
		echo "<font color=green>NULL</font>";
	}elseif($elem === 0){
		echo "0";
	}elseif($elem === true){
		echo "<font color=green>TRUE</font>";
	}elseif($elem === false){
		echo "<font color=green>FALSE</font>";
	}elseif($elem === ""){
		echo "<font color=green>EMPTY STRING</font>";
	}else{
		echo str_replace("\n","<strong><font color=red>*</font></strong><br>\n",htmlentities($elem));
	}
}

/**
 * Retourne TRUE ssi $item est dans $array (recherche en profondeur)
 * @param mixed $item
 * @param array $array
 */
function in_array_r($item , $array){
	return preg_match('/"'.$item.'"/i' , json_encode($array));
}

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


/**
 * Fonction appelé par djikweb/testing/page
 * @return string
 */
function dw_tools_testing_page() {
  
  $files = drupal_system_listing('/^' . DRUPAL_PHP_FUNCTION_PATTERN . '\.info$/', 'modules', 'name', 0);
  $files = $files['dw_tools'];
  print_nice($files->uri);
  $info = file_get_contents($files->uri);
  
  
  var_dump($info);
  print_nice(stripos($info,'7.x-2.0-alpha2'));
  
  
  
	return 'page djikweb/testing/page';
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


/**
 * Fonction qui permet de récupérer la valeur par défault d'un composant RADIO
 * @param unknown $variable
 * @return Zéro or Value
 */
function _get_default_value($variable){
	if ($variable == ''){
		$value = 0;
	} else {
		$value = $variable;
	}
	
	return $value;
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




