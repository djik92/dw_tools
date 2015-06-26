<?php 

/**
 * Implementation of hook_drush_command().
 * @author djik
 * @return array
 */
function dw_tools_drush_command() {
	$items = array();

	$items['dw-tools-clear-table-deleted'] = array(
			'description' 		=> dt('To purge the data archived by Drupal.'),
			'aliases' 			=> array('dw-clear'),
		
	);
	
	$items['dw-tools-truncate-table-cache'] = array(
	    'description' 		=> dt('truncate table cache.'),
	    'aliases' 			=> array('ccc'),

	);
	
	
	return $items;
}

/**
 * Function executed with drush dw-clear command
 * @link dw-tools-clear-table-deleted
 * @uses drush dw-clear
 * @author djik
 * @return NULL
 */
function drush_dw_tools_clear_table_deleted() {
   
  //Suppression des tables field_deleted_data_%
  $result = db_query("SELECT CONCAT( 'DROP TABLE IF EXISTS ', table_name , '' )
    AS statement FROM information_schema.tables
    WHERE table_name LIKE 'field_deleted_data_%'");
  
  foreach ($result as $v){
    db_query($v->statement);
  }
  watchdog('drush', t('Prefixed \'field_deleted_data_\' tables are deleted'));
  drush_print_r(dt('Prefixed \'field_deleted_data_\' tables are deleted'));
  
  
  //Suppression des tables field_deleted_revision_%
  $result = db_query("SELECT CONCAT( 'DROP TABLE IF EXISTS ', table_name , '' ) 
    AS statement FROM information_schema.tables 
    WHERE table_name LIKE 'field_deleted_revision_%'");
  
  foreach ($result as $v){
    db_query($v->statement);
  }
  watchdog('drush', t('Prefixed \'field_deleted_revision_\' tables are deleted'));
  drush_print_r(dt('Prefixed \'field_deleted_revision_\' tables are deleted'));
  
  
  //Suppression des lignes dans field_config
  $result = db_delete('field_config')
            ->condition('deleted', '1')
            ->execute();
  watchdog('drush', t('The lines of the table \'field_config\' where  deleted = 1 was deleted'));
  drush_print_r(dt('The lines of the table \'field_config\' where  deleted = 1 was deleted'));
  
  //Suppression des lignes dans field_config_instance
  $result = db_delete('field_config_instance')
            ->condition('deleted', '1')
            ->execute();
  watchdog('drush', t('The lines of the table \'field_config_instance\' where  deleted = 1 was deleted'));
  drush_print_r(dt('The lines of the table \'field_config_instance\' where  deleted = 1 was deleted'));
  
  
}

/**
 * Function executed with drush ccc command
 * @link dw-tools-truncate-table-cache
 * @uses drush ccc
 * @author djik
 * @return NULL
 */
function drush_dw_tools_truncate_table_cache(){
 
  $result = db_query("SELECT table_name AS statement FROM information_schema.tables WHERE table_name LIKE 'cache%'");
  
  foreach ($result as $table){
    db_truncate($table->statement);
    drush_log(dt('@tables tables are truncated.', array('@tables' => $table->statement)), 'success');
  }
  
}

