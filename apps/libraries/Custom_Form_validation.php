<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Form_validation - extended from original library
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Custom_Form_validation extends StepRite_Form_validation {

    public function __construct()
    {
        parent::__construct();
    }

    // --------------------------------------------------------------------

    /**
     * Valid Date (ISO format)
     *
     * @access    public
     * @param    string
     * @return    bool
     */
    function valid_date($date)
    {
        if (!empty($date))
        {
            if (preg_match("/^([0-9]{4})-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$/", $date, $values))
            {
			$month = $values[2];
			$day = $values[3];
			$year = $values[1];
			
                if (checkdate($month, $day, $year))    // Date actually exists
                {
					
                    return TRUE;
                }
            }
        }
        return FALSE;
    } 
}