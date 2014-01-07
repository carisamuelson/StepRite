<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed'); 
/***************************************************************************
|--------------------------------------------------------------------------
| User Library
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 06 January 2014
| All information included is copyrighted MedHab, LLC 2013-2014
|
***************************************************************************/
class User {
	protected $_StepRite;
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Constructor
	|--------------------------------------------------------------------------
	| @access 	private
	| @param	none
	| @return	none
	***************************************************************************/		
	function __construct() {
		$this->_StepRite =& get_instance();
	}

	/***************************************************************************
	|--------------------------------------------------------------------------
	| is_valid
	|--------------------------------------------------------------------------
	| @access	public
	| @param	string, string
	| @return	integer (0 if false, user_id otherwise)
	***************************************************************************/		
    public function is_valid($email, $password) {
		
		$query = $this->_StepRite->db->where('email', $email)->get('users');
		
		if(!$query->num_rows()) { return 0; }
		
		$user = $query->row_array();
		
		if($user['active'] && $password == $this->_StepRite->encrypt->decode($user['password'])) {
			return $user['id'];
		}
		
		return 0;
    }
}
/* End of file User.php */
/* File location: apps/libraries/User.php */