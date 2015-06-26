<?php

/**
 * Same a dpm() in php
 * @author joechrysler
 * 
 * @link https://github.com/joechrysler/xtac/blob/master/php/print_nice.php
 * 
 * @param $elem
 *      Element to analyze
 * @param $max_level
 *      Max level
 * @param $print_nice_stack
 * 
 * @return NULL
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
 * Allow get a default value of radio select box
 * @param $variable
 * @return Value or FALSE
 */
function _get_default_value($variable){
  
  $return = FALSE;
  
  if (!empty($variable)){
    $return = $variable;
  }

  return $return;
}

/**
 * Allow to get a current nid
 * 
 * @author coreyp_1
 * @link https://www.drupal.org/node/160921
 * 
 * @return FALSE or NID
 *      Find : Nid
 *      Not Find : FALSE
 */
function _get_current_nodeid(){
  
  $nodeid = FALSE;
  if (arg(0) == 'node' && is_numeric(arg(1))){
    $nodeid = arg(1);
  }
  return $nodeid; 
}

/**
 * Allow to get a module file *.info
 * @author djik
 * @param  $module_name
 *     Name of module
 * @return string
 */
function _get_file_info($module_name){
  $files = drupal_system_listing('/^' . DRUPAL_PHP_FUNCTION_PATTERN . '\.info$/', 'modules', 'name', 0);
  $files = $files[$module_name];

  return file_get_contents($files->uri);
}
