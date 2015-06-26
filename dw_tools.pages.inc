<?php

/**
 * Form who allow to collect a new password
 * @link djikweb/generate/password
 * @param $form
 * @param $form_state
 * @return array
 */
function dw_tools_generate_password($form, &$form_state) {

  $form['passwd'] = array(
      '#type' 				=> 'textfield',
      '#title' 				=> t('Password'),
      '#default_value' 		=> '',
      '#size' 				=> 60,
      '#maxlength' 			=> 128,
      '#required' 			=> TRUE,

  );

  $form['submit_button'] = array(
      '#type' 				=> 'submit',
      '#value' 				=> t('Check'),
  );

  return $form;

}

/**
 * Form Submit who allow display Query SQL Update password
 * @param $form
 * @param $form_state
 * @return NULL
 */
function dw_tools_generate_password_submit($form, &$form_state) {

  require_once getcwd().'/includes/password.inc';
  require_once getcwd().'/includes/bootstrap.inc';


  $hash_pass =  user_hash_password($form_state['input']['passwd'],11);

  $txt = 'UPDATE users SET pass=\''.$hash_pass.'\' WHERE uid=1;';
  dsm($txt);
}

/**
 * Allow to test a code
 *
 * @link admin/config/development/djikweb/page
 * @return string
 */
function dw_tools_testing_page() {
  
  /**
   * Insert a code
   */
  return 'page Test';
}

/**
 * Allow to create a script for create a Mysql Database
 * @link djikweb/generate/install/mysql
 * @param $form
 * @param $form_state
 * @return array
 */
function dw_tools_generate_install_mysql($form, &$form_state) {
  $form['field_login'] = array(
      '#type' 				=> 'textfield',
      '#title' 				=> t('Login'),
      '#default_value' 		=> '',
      '#size' 				=> 60,
      '#maxlength' 			=> 128,
      '#required' 			=> TRUE,

  );

  $form['field_passwd'] = array(
      '#type' 				=> 'password',
      '#title' 				=> t('Password'),
      '#maxlength' 			=> 64,
      '#size' 				=> 30,
      '#maxlength' 			=> 128,
      '#required' 			=> FALSE,
      	
  );

  $form['field_bdd'] = array(
      '#type' 				=> 'textfield',
      '#title' 				=> t('Database Name'),
      '#default_value' 		=> '',
      '#size' 				=> 60,
      '#maxlength' 			=> 128,
      '#required' 			=> TRUE,

  );

  $form['del_bdd'] = array(
      '#type' 			=> 'radios',
      '#title' 			=> t('You want to remove the database (if exists) ?'),
      '#default_value' 	=> 0,
      '#options' 			=> array(
          0 	=> t('No'),
          1 	=> t('Yes'),
      ),
      '#required' 		=> TRUE,
  );

  $form['submit_button'] = array(
      '#type' 				=> 'submit',
      '#value' 				=> t('Check'),
  );

  return $form;
}

/**
 * Form submit to generate a script Mysql
 * @param unknown $form
 * @param unknown $form_state
 * @return NULL
 */
function dw_tools_generate_install_mysql_submit($form, &$form_state) {
 
  $txt = '';

  if($form_state['input']['del_bdd']){
    $txt .= 'DROP DATABASE IF EXISTS '.strtoupper($form_state['input']['field_bdd']).';'."\n";
  }
  $txt .= 'CREATE DATABASE IF NOT EXISTS '.strtoupper($form_state['input']['field_bdd']).';'."\n";

  if(strtoupper($form_state['input']['field_login']) != 'ROOT'){
    $txt .= 'use '.strtoupper($form_state['input']['field_bdd']).';'."\n";
    $txt .= "GRANT ALL PRIVILEGES ON ".$form_state['input']['field_bdd'].".* TO '".$form_state['input']['field_login']."'@'localhost' IDENTIFIED BY '".$form_state['input']['field_passwd']."' WITH GRANT OPTION;"."\n";
    $txt .= 'FLUSH PRIVILEGES;'."\n";
  }
  dsm($txt);
}




