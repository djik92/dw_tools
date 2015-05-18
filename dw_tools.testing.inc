<?php


/**
 * Fonction appelé par djikweb/testing/page
 * @return string
 */
function dw_tools_testing_page() {

/*  
  

$ciid = db_select('commercial_item','ci')
    ->fields('ci',array('ciid'))
    ->condition('uuid','urn:bossanova:commercial_unit:08ff27bc-2ce4-4bac-a779-520a240c3afe','=')
    ->execute()
    ->fetchField();

print_nice($ciids);*/
 /*   $query = db_select('commercial_authority','ca')
    ->fields('ca',array('title'))
    ->condition('type','webform_zones','=')
    ->condition('title',$sw->form_zonning_label,'=')
    ->execute();
  
    if($query->rowCount() > 0){
  
      $label = db_select('commercial_authority','ca')
      ->fields('ca',array('title'))
      ->condition('type','webform_zones','=')
      ->condition('code',$sw->form_zonning_label,'=')
      ->execute()
      ->fetchField();
  
      db_update('studialis_webform')
      ->fields(array(
          'form_zonning_uuid' => $sw->form_zonning_label,
          'form_zonning_label' => $label,
      ))
      ->condition('nid',$sw->nid,'=')
      ->execute();
       
    }
  }*/
  
  
  
/*


$account = user_load_by_name('webdev');
if (user_check_password('rbzo45',$account)) {
  print "<br />Yes";
} else {
  print "<br />No";
}
 */

//UPDATE user SET pass='$S$CpiOFftf4apILxJCsVJGb09ijB11HLGjBDp2XbfofmpiqOa&b2c' where uid='1'

  //print_nice($_SERVER['SERVER_NAME']);

  
  /*
  SELECT vid FROM views_view WHERE name = 'your_views_machine_name';
  DELETE FROM views_view WHERE vid = id_from_above;
  DELETE FROM views_display WHERE vid = id_from_above;
*/
  return 'page Test';
}