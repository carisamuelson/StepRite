<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Article Management Model
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/

class Articles_model extends StepRite_Model {
	
	public function get_articles() {
		return $this->db->query('SELECT * FROM `articles` ORDER BY `articles`.`entry_date` DESC LIMIT 6');
	}
}