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
			//'bootstrap' 		=> DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
	);
	
	return $items;
}



/**
 * Fonction qui est executer lors de l'appel de drush cfib
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

