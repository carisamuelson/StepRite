<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

// see http://www.androidhive.info/2012/01/android-json-parsing-tutorial/ for android JSON parsing

	define('CLEAR_KEY', '9Wb90t3OZ8g4tRG2vmtsh3xc6nh2wPOvLdDF9GEImH8cNmX34aWPr3VMBsHVog3');
	define('SUCCESS', 1);
	define('ERR_AUTH', -1);
	define('ERR_DB', -2);
	define('ERR_UPLOAD', -3);
	
	date_default_timezone_set('UTC');
	
// docblocks formatted for use by Doxygen
/**
* <b>Description:</b>
* <p>This class implements a web service that facilitates communication between the smartphone apps and the database.</p>
* <p>The relevant requirements include:</p>
* <ul>
* <li>The smartphone shall be able to send a login request and receive a response indicating whether or not the login request was accepted or not.</li>
* <li>The smartphone shall be able to send a regimen request and receive a response that includes the entire user regimen.</li>
* <li>The service shall be able to 
* 	<ul>
* 		<li>receive exercise files from the smartphone app, </li>
* 		<li>deliver the files to the proper algorithms, </li>
* 		<li>insert the resulting output to the database, </li>
* 		<li>and archive the raw files.</li>
* 	</ul>
* </li>
* </ul>
*/	
class Appservice extends StepRite_Controller 
{	
	/**
	* <b>Description:</b>
	* - This function serves as the authenticating entry point for the smartphone apps to communicate with the database
	* - receives a POST request containing a username and password
	* - determines if the username and password are associated with an active account
	* - if the account is valid, generates an md5 token, which is saved in sr_token
	* - returns a JSON value containing 
	*		- a success or fail value
	*		- the token generated upon valid authentication
	* @test Make sure the login token is being inserted into the sr_token table
	*/
	public function login()
	{
		$username = $this->input->post('username'); // RECEIVE POST VALUES
		$password = $this->input->post('password'); 	
		
		// FORM VALIDATION
		$this->load->library('form_validation');	
		$this->form_validation->set_rules('username', 'Username', 'required');
		$this->form_validation->set_rules('password', 'Password', 'required');

		if ($this->form_validation->run() == FALSE) // RUN FORM VALIDATION
		{
			$data['result'] = ERR_AUTH;
		}
		else
		{			
			$patient_id = $this->getUserID($username,$password); // GET USER ID FROM UN/PW
			if ( $patient_id < 0 )
			{
				$data['result'] = ERR_AUTH;
			}
			else
			{
				$token = md5($username . "" . rand() ); // GENERATE TOKEN
				
				$this->load->model("appservicemodel");
				$newEntry = array 
					(
					'patient_id' => $patient_id, 
					'token' => $token
					);
					
				if ( $this->appservicemodel->insert_token($newEntry) ) // INSERT TOKEN INTO sr_table
				{
					$data['result'] = SUCCESS;
					$data['token'] = $token;
				}				
				else
				{
					$data['result'] = ERR_DB;
				}
			}
		}		

		$this->form_validation->clear_field_data();	// see MY_Form_validation.php		

		echo json_encode( $data ); // echo for proper REST return format
		return json_encode( $data ); // return value for ability to unit test
	}

	public function get_regimen()
	{
		$token = $this->input->post('token'); // RECEIVE POST VALUES
		
		// FORM VALIDATION
		$this->load->library('form_validation');

		$this->form_validation->set_rules('token', 'Token', 'required');

		if ($this->form_validation->run() == FALSE) // RUN FORM VALIDATION
		{
			$data['result'] = ERR_AUTH;
		}
		else
		{
			$this->load->model("appservicemodel");
			$patient_id = $this->appservicemodel->get_user_id_from_token($token); // GET USER ID FROM TOKEN TABLE
			if ( $patient_id == NULL )
			{
				$data['result'] = ERR_AUTH;
			}
			else
			{
				$data['result'] = SUCCESS;
				$data['regimens'] = $this->appservicemodel->get_regimen($patient_id); // GET REGIMEN FROM USER ID
			}
		}
		
		$this->form_validation->clear_field_data();	// see MY_Form_Validation.php

		// for testing, see http://www.jsoneditoronline.org/
		echo json_encode( $data ); // echo for proper REST return format
		return json_encode( $data ); // return value for ability to unit test
	}
	
	public function upload_exercise()
	{
		$token = $this->input->post('token'); // RECEIVE POST VALUES	
		$regimenID = $this->input->post('regimenID'); // RECEIVE POST VALUES	
			// FORM VALIDATION
		$this->load->library('form_validation');

		$this->form_validation->set_rules('token', 'Token', 'required');
		$this->form_validation->set_rules('regimenID', 'Regimen ID', 'required');

		$this->db->trans_start();
		
		$files_array = null;
		$path_upload = FCPATH . 'uploads' . DIRECTORY_SEPARATOR;
		$path_algorithm = FCPATH . 'algorithms' . DIRECTORY_SEPARATOR;
		
		if ($this->form_validation->run() == FALSE) // RUN FORM VALIDATION
		{
			$data['result'] = ERR_AUTH;
		}
		else
		{
			$this->load->model("appservicemodel");
			$patient_id = $this->appservicemodel->get_user_id_from_token($token); // GET USER ID FROM TOKEN TABLE
			if ( $patient_id == NULL )
			{
				$data['result'] = ERR_AUTH;
			}
			else
			{
				$regimen_owner = $this->appservicemodel->get_regimen_owner($regimenID);
				
				if ( $patient_id != $regimen_owner)
				{
					$data['result'] = ERR_AUTH;
				}
				else
				{
				
					$exercise_type = $this->appservicemodel->get_exercise_type_from_regimen_id($regimenID);
										
					$config['upload_path'] = $path_upload;
					$config['allowed_types'] = "csv";
					$config['max_size']	= '999999';
					$config['overwrite'] = TRUE;
					$regimen_count = $this->appservicemodel->get_regimen_count($regimenID);
					$exercise_id = $this->appservicemodel->get_exercise_id_from_regimen_id($regimenID);
					$this->load->library('upload');
					$this->load->helper('file');
					
					$directory = $path_upload;
					$raw_base_name = $regimenID . "_" . $regimen_count;
					$base_name = "t_" . $raw_base_name;
					$file_path = $directory . $base_name;
					
					$epoch = $this->input->post('epoch'); // RECEIVE POST VALUE
					$date_time = date("Y-m-d H:i:s", $epoch);

					
					if ( $exercise_type == 1 ) // gait
					{
						
						if 	( 	empty($_FILES['file0l']['name']) ||
								empty($_FILES['file0r']['name']) ||
								empty($_FILES['file1l']['name']) ||
								empty($_FILES['file1r']['name']) ||
								empty($_FILES['file2l']['name']) ||
								empty($_FILES['file2r']['name']) ||
								empty($_FILES['file3l']['name']) ||
								empty($_FILES['file3r']['name'])	)
						{
							$data['result'] = ERR_UPLOAD;
							$data['err'] = 'missing files';
						}
						else 
						{
							$valid = true;
							
							for ($runID = 0; $runID < 4; $runID++)
							{	
								$raw_filename  = "r_" . $regimenID ."_". $regimen_count . "-" . "lf" . $runID . ".csv";
								$temp_filename_left = "t_" . $regimenID ."_". $regimen_count . "-" . "lf" . $runID . ".csv";
								$temp_filepath_left = $directory.$temp_filename_left;
								
								$config['file_name'] = $raw_filename;
								$this->upload->initialize($config); //initiate the upload library as per http://ellislab.com/forums/viewthread/208101/#968005
								$this->upload->do_upload("file".$runID."l");
								copy($directory.$raw_filename, $temp_filepath_left);
								$files_array[] = $raw_filename;
								$files_array[] = $temp_filename_left;
								
								$result = $this->upload->data();
								
								$raw_filename  = "r_". $regimenID ."_". $regimen_count . "-" . "rf" . $runID . ".csv";
								$temp_filename_right = "t_". $regimenID ."_". $regimen_count . "-" . "rf" . $runID . ".csv";
								$temp_filepath_right = $directory.$temp_filename_right;
								
								$config['file_name'] = $raw_filename;
								$this->upload->initialize($config); //initiate the upload library as per http://ellislab.com/forums/viewthread/208101/#968005
								$this->upload->do_upload("file".$runID."r");
								copy($directory.$raw_filename, $temp_filepath_right);
								$files_array[] = $raw_filename;
								$files_array[] = $temp_filename_right;

								$result = $this->upload->data();
								
								$difference = $this->input->post('diff'.$runID); // RECEIVE POST VALUE

								
								//	EXECUTE SYNC
								exec($path_algorithm."wrapper $temp_filepath_left $temp_filepath_right $difference", $output);
								var_dump($output);
								// EXECUTE GAIT ALGORITHM
								exec($path_algorithm."dist $file_path $runID", $output);

								if ($runID == 0 )
								{
									$files_array[] = $base_name . ".ini";
								}
								else
								{

									// EXECUTE PRESSURE ALGORITHM
									$output = null;
									exec($path_algorithm."calc_force $temp_filepath_left $temp_filepath_right", $output);
								
									rename($file_path.".out", $file_path."-".$runID.".out");								
									$file_contents_string = read_file($file_path . "-".$runID.".out");
									
									$files_array[] = $base_name . "-".$runID.".out";
									
									$file_contents_array = explode("\n",$file_contents_string);
									// GET PRESSURE VALUES
										$regimenID = $regimenID;
										$regimen_count = $regimen_count;
										$runID = $runID;
										$left_average_pressure = $output[0];
										$left_maximum_pressure = $output[1];
										$right_average_pressure = $output[2];
										$right_maximum_pressure = $output[3];
										$num_elements_pressure = $output[4];
										$lf1 = $output[5];
										$lf2 = $output[6];
										$lf3 = $output[7];
										$lf4 = $output[8];
										$rf1 = $output[9];
										$rf2 = $output[10];
										$rf3 = $output[11];
										$rf4 = $output[12];

										$index = 16;
										$clock_time = $file_contents_array[$index++];
										$avg_cadence_time = $file_contents_array[$index++];
										$number_of_strides = $file_contents_array[$index++];
										$LF_avg_swing_time = $file_contents_array[$index++];
										$RF_avg_swing_time = $file_contents_array[$index++];
										$LF_RF_avg_step_time = $file_contents_array[$index++];
										$RF_LF_avg_step_time = $file_contents_array[$index++];
										$LF_avg_maximum_pressure = $file_contents_array[$index++];
										$RF_avg_maximum_pressure = $file_contents_array[$index++];
										$LF_avg_stride_distance = $file_contents_array[$index++]; 
										$RF_avg_stride_distance = $file_contents_array[$index++];

									$input_left = array (
										'protocol_id' => $regimenID,
										'protocol_num' => $regimen_count,
										'runID' => $runID,
										'foot' => '0',
										'avg_pressure' => $left_average_pressure,
										'max_pressure' => $left_maximum_pressure,
										'num_elements' => $num_elements_pressure,
										'f1' => $lf1,
										'f2' => $lf2,
										'f3' => $lf3,
										'f4' => $lf4,
										'clock_time' => $clock_time,
										'avg_cadence_time' => $avg_cadence_time,
										'number_of_strides' => $number_of_strides,
										'avg_swing_time' => $LF_avg_swing_time,
										'avg_step_time' => $LF_RF_avg_step_time,
										'avg_max_pressure' => $LF_avg_maximum_pressure,
										'avg_stride_distance' => $LF_avg_stride_distance,
									);
									
									$input_right = array (
										'protocol_id' => $regimenID,
										'protocol_num' => $regimen_count,
										'runID' => $runID,
										'foot' => '1',
										'avg_pressure' => $right_average_pressure,
										'max_pressure' => $right_maximum_pressure,
										'num_elements' => $num_elements_pressure,
										'f1' => $rf1,
										'f2' => $rf2,
										'f3' => $rf3,
										'f4' => $rf4,
										'clock_time' => $clock_time,
										'avg_cadence_time' => $avg_cadence_time,
										'number_of_strides' => $number_of_strides,
										'avg_swing_time' => $RF_avg_swing_time,
										'avg_step_time' => $RF_LF_avg_step_time,
										'avg_max_pressure' => $RF_avg_maximum_pressure,
										'avg_stride_distance' => $RF_avg_stride_distance,
									);
									
									if (!$this->appservicemodel->insert_gait($input_left) ||
										!$this->appservicemodel->insert_gait($input_right)
										)
									{
										$data['result'] = ERR_DB;
										$valid = false;
										break;
									}
									
								}
							}
							
							if ( $valid == true )
							{		
								$input_left = array (
									'patient_id' => $patient_id,
									'protocol_id' => $regimenID,
									'date_time' => $date_time,
									'exercise_id' => $exercise_id,
									'left_calc' => 0,
									'right_calc' => 0,
								);
								
								$input_right = array (

									'patient_id' => $patient_id,
									'protocol_id' => $regimenID,
									'date_time' => $date_time,
									'exercise_id' => $exercise_id,
									'left_calc' => 0,
									'right_calc' => 0,
								);
								
								if (!$this->appservicemodel->insert_activity($input_left) ||
									!$this->appservicemodel->insert_activity($input_right) 
									)
								{
									$data['result'] = ERR_DB;
								}
								else
								{
									$data['result'] = SUCCESS;
								}
							}
						}
					}
					elseif ( $exercise_type == 2 ) // force
					{
						
						if 	( 	empty($_FILES['file1l']['name']) ||
								empty($_FILES['file1r']['name']) )
						{
							$data['result'] = ERR_UPLOAD;
						}
						else 
						{
							
							$runID = 1;
							$raw_filename  = "r_" . $regimenID ."_". $regimen_count . "-" . "lf" . $runID . ".csv";
							$temp_filename_left = "t_" . $regimenID ."_". $regimen_count . "-" . "lf" . $runID . ".csv";
							$temp_filepath_left = $directory.$temp_filename_left;
							
							$config['file_name'] = $raw_filename;
							$this->upload->initialize($config); //initiate the upload library as per http://ellislab.com/forums/viewthread/208101/#968005
							$this->upload->do_upload("file".$runID."l");
							copy($directory.$raw_filename, $temp_filepath_left);
							$files_array[] = $raw_filename;
							$files_array[] = $temp_filename_left;
							
							$result = $this->upload->data();
							
							$raw_filename  = "r_". $regimenID ."_". $regimen_count . "-" . "rf" . $runID . ".csv";
							$temp_filename_right = "t_". $regimenID ."_". $regimen_count . "-" . "rf" . $runID . ".csv";
							$temp_filepath_right = $directory.$temp_filename_right;
							
							$config['file_name'] = $raw_filename;
							$this->upload->initialize($config); //initiate the upload library as per http://ellislab.com/forums/viewthread/208101/#968005
							$this->upload->do_upload("file".$runID."r");
							copy($directory.$raw_filename, $temp_filepath_right);
							$files_array[] = $raw_filename;
							$files_array[] = $temp_filename_right;


							$result = $this->upload->data();
							
							$difference = $this->input->post('diff1'); // RECEIVE POST VALUE
							
							//	EXECUTE SYNC
							exec($path_algorithm."wrapper $temp_filepath_left $temp_filepath_right $difference", $output);
							// EXECUTE PRESSURE ALGORITHM
							$output = null;
							exec($path_algorithm."calc_force $temp_filepath_left $temp_filepath_right", $output);
							
							// LEFT ENTRY
							$inputLeft = array (
								'average' => $output[0],
								'min' => 0,
								'max' => $output[1],
								'over_max' => 0,
								'under_min' => 0,
								'time' => $output[4] / 10, // pressure exercises recorded at 10hz
								'force1' => $output[5],
								'force2' => $output[6],
								'force3' => $output[7],
								'force4' => $output[8],
							);
							
							// RIGHT ENTRY
							$inputRight = array (
								'average' => $output[2],
								'min' => 0,
								'max' => $output[3],
								'over_max' => 0,
								'under_min' => 0,
								'time' => $output[4] / 10, // pressure exercises recorded at 10hz
								'force1' => $output[9],
								'force2' => $output[10],
								'force3' => $output[11],
								'force4' => $output[12],
							);
							
							if (!$this->appservicemodel->insert_force($inputLeft) )
							{
								$data['result'] = ERR_DB;
							}
							$leftcalc = $this->db->insert_id();
							if (!$this->appservicemodel->insert_force($inputRight) )
							{
								$data['result'] = ERR_DB;
							}
							$rightcalc = $this->db->insert_id();
	
							$input = array (
								'patient_id' => $patient_id,
								'protocol_id' => $regimenID,
								'date_time' => $date_time,
								'exercise_id' => $exercise_id,
								'left_calc' => $leftcalc,
								'right_calc' => $rightcalc,
							);
							
							if (!$this->appservicemodel->insert_activity($input) )
							{
								$data['result'] = ERR_DB;
							}
							else
							{
								$data['result'] = SUCCESS;
							}
						}
					}
					elseif ( $exercise_type == 3 ) // rom
					{
						if 	( 	empty($_FILES['file1l']['name']) ||
								empty($_FILES['file1r']['name']) )
						{
							$data['result'] = ERR_UPLOAD;
						}
						else 
						{							
							$runID = 1;
							$raw_filename  = "r_" . $regimenID ."_". $regimen_count . "-" . "lf" . $runID . ".csv";
							$temp_filename_left = "t_" . $regimenID ."_". $regimen_count . "-" . "lf" . $runID . ".csv";
							$temp_filepath_left = $directory.$temp_filename_left;
							
							$config['file_name'] = $raw_filename;
							$this->upload->initialize($config); //initiate the upload library as per http://ellislab.com/forums/viewthread/208101/#968005
							$this->upload->do_upload("file".$runID."l");
							copy($directory.$raw_filename, $temp_filepath_left);
								$files_array[] = $raw_filename;
							$files_array[] = $temp_filename_left;
							
							$result = $this->upload->data();
							
							$raw_filename  = "r_". $regimenID ."_". $regimen_count . "-" . "rf" . $runID . ".csv";
							$temp_filename_right = "t_". $regimenID ."_". $regimen_count . "-" . "rf" . $runID . ".csv";
							$temp_filepath_right = $directory.$temp_filename_right;
							
							$config['file_name'] = $raw_filename;
							$this->upload->initialize($config); //initiate the upload library as per http://ellislab.com/forums/viewthread/208101/#968005
							$this->upload->do_upload("file".$runID."r");
							copy($directory.$raw_filename, $temp_filepath_right);
								$files_array[] = $raw_filename;
							$files_array[] = $temp_filename_right;

							$result = $this->upload->data();
							
							$difference = $this->input->post('diff1'); // RECEIVE POST VALUE
							
							//	EXECUTE SYNC
							exec($path_algorithm."wrapper $temp_filepath_left $temp_filepath_right $difference", $output);
							// EXECUTE ROM ALGORITHM
							$output = null;
							exec($path_algorithm."calc_rom $temp_filepath_left $temp_filepath_right $exercise_id", $output);	

							// LEFT ENTRY
							$inputLeft = array (
								'average' => $output[2], // avgRange;
								'minimum' => $output[0], // minRange;
								'maximum' => $output[1], // maxRange;
								'reps' => $output[6], // reps;
								'time' => $output[7] / 10, // num_degrees; // assuming 10hz
								'rep_average' => $output[5],// rep_avg;
								'rep_min' => $output[3],// rep_min;
								'rep_max' => $output[4] ,// rep_max;
								'force1' => $output[16],
								'force2' => $output[17],
								'force3' => $output[18],
								'force4' => $output[19],
							);
							
							// RIGHT ENTRY
							$inputRight = array (
								'average' => $output[10], // avgRange;
								'minimum' => $output[8], // minRange;
								'maximum' => $output[9], // maxRange;
								'reps' => $output[14], // reps;
								'time' => $output[15] / 10, // num_degrees; // assuming 10hz
								'rep_average' => $output[13],// rep_avg;
								'rep_min' => $output[11],// rep_min;
								'rep_max' => $output[12] ,// rep_max;
								'force1' => $output[20],
								'force2' => $output[21],
								'force3' => $output[22],
								'force4' => $output[23],
							);
							
							if (!$this->appservicemodel->insert_rom($inputLeft) )
							{
								$data['result'] = ERR_DB;
							}
							$leftcalc = $this->db->insert_id();
							if (!$this->appservicemodel->insert_rom($inputRight) )
							{
								$data['result'] = ERR_DB;
							}
							$rightcalc = $this->db->insert_id();

							$input = array (
								'patient_id' => $patient_id,
								'protocol_id' => $regimenID,
								'date_time' => $date_time,
								'exercise_id' => $exercise_id,
								'left_calc' => $leftcalc,
								'right_calc' => $rightcalc,
							);
							
							if (!$this->appservicemodel->insert_activity($input) )
							{
								$data['result'] = ERR_DB;
							}
							else
							{
								$data['result'] = SUCCESS;
							}	
						}
					}
					else
					{
						$data['result'] = ERR_UPLOAD;
						$data['err'] = "unknown type";
					}
					
				}
			}
		}
		
		$this->db->trans_complete();
		
		// ARCHIVE RAW AND DELETE TEMP FILES	
		$directory1 = $path_upload;
		$directory2 = $path_algorithm;
		if ( $files_array != null )
		{
			foreach ($files_array as $file)
			{
				if ( pathinfo($file, PATHINFO_EXTENSION) )
				{
					if ( $file[0] == 'r' ) // if file name begins with "r" for "raw"
					{
						rename($directory1.$file, $directory2.$file);
					}
					else 
					{
						unlink($directory1.$file);
					}
				}
			}
		}
			
		// CLEAR FORM VALIDATION RULES 
		$this->form_validation->clear_field_data();	// see MY_Form_Validation.php

		// for testing, see http://www.jsoneditoronline.org/
		echo json_encode( $data ); // echo for proper REST return format
		return json_encode( $data ); // return value for ability to unit test
	}
	
	
	
	/**
	* <b>Description:</b>
	* <p>This function empties the sr_tokens table. 
	* As a security measure, appservice login tokens should be emptied regularly. 
	* This function can be called regularly from a cron job.
	* As a security measure, the function requires a pre-defined key to successfully execute.
	* The cron job should be provided this key.</p>
	* @test Make sure the clear_token() function empties the sr_token table
	*/
	public function clear_tokens($key = "")
	{
		if ( $key != CLEAR_KEY )
		{
			return FALSE;
		}
		else
		{
			$this->load->model("appservicemodel");
			return $this->appservicemodel->clear_tokens() ? TRUE : FALSE;
		}
	}
	
	/**
	* <b>Description:</b>
	* <p>This function is a temporary stand-in for a proper library function</p>
	* @todo Replace this getUserID function with a proper library function
	*/
	private function getUserID($email, $password) // replace with library function
	{

        // Load the Library
        $this->load->library('user');
       
        // Check if valid
        if($id = $this->user->is_valid($email, $password)) 
		{
            /* Do something with $id */
			return $id;
        }
        else 
		{
            /* validity failed */
			return -1;
        }	
	}

	/**
	* <b>Description:</b>
	* - This function can be called from the URL to run unit tests.
	* <pre>/StepRite/index.php/appservice/test</pre>
	* - It will only run when the ENVIRONMENT global is set as 'development' or 'testing'
	* - Each test runs database queries as transactions in test mode
	* so that all changes made by the unit tests will be rolled back.</p>
	*/
	public function test()
	{
		if ( ENVIRONMENT == 'development' || ENVIRONMENT == 'testing' )
		{
			$this->load->library('unit_test');
			$this->unit->set_test_items(array('test_name', 'result')); 
			
			$this->test_getUserID_success_62();
			$this->test_getUserID_success_63();
			$this->test_getUserID_success_64();
			$this->test_getUserID_success_65();
			$this->test_getUserID_fail_inactive_66();

			$this->test_login_success();
			$this->test_login_missing_username();
			$this->test_login_missing_password();

			$this->test_get_regimen_success();
			$this->test_get_regimen_missing_token();
			$this->test_get_regimen_invalid_token();
			
			//$this->test_clear_tokens_invalid_key();
			//$this->test_clear_tokens_success();
			
			$this->print_test_results();
		}
		else
		{
			show_404();
		}
	}
	
	/**
	* <b>Description:</b>
	* <p>This function changes the format of the presentation of unit test results.</p>
	*/
	private function print_test_results()
	{
		echo "<h1>AppService Tests</h1>";
		echo "<table border=1>";
		echo "<th>Test ID</th>";
		echo "<th>Test Name</th>";
		echo "<th>Description</th>";
		echo "<th>Result</th>";
		
		foreach ( $this->unit->result() as $key => $value )
		{				
			echo "<tr>";
			
			$test_number = "T-" . "AS-" . $key; // Test(T), AppService (AS)
			echo "<td>".$test_number."</td>";
			
			echo "<td>".$value['Test Name']."</td>";

			echo "<td>".$value['Notes']."</td>";
			
			if ( $value['Result'] == 'Passed' ) $color = 'green';
			if ( $value['Result'] == 'Failed' ) $color = 'red';
			echo "<td><font color=$color>".$value['Result']."</td>";

			echo "</tr>";
			
		}
		
		echo "</table>";
			
	}
	
	private function test_get_regimen_success()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back
		$test_name = "test_get_regimen_success()";
		$notes = "<p>This method checks that the correct regimen is returned given a specific user ID.</p>";

		$_POST['token'] = '2dd7031d3ad534445b8100d23b181de7';
		$actual = $this->get_regimen();
		$expected = '{"result":1,"regimens":[{"RegimenID":"68","ExerciseID":"4","reps":"3","hold":"5","weight":"9","isometric":"0","ExerciseName":"Walk - 20 Steps","timesPerDay":"3"},{"RegimenID":"69","ExerciseID":"26","reps":"1","hold":"2","weight":"3","isometric":"0","ExerciseName":"Balance on Foam with Eyes Closed","timesPerDay":"3"}]}';		
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		unset($_POST);
		$this->db->trans_complete();
	}
	
	private function test_get_regimen_missing_token()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back

		$test_name = "test_get_regimen_missing_token()";
		$notes = "This method makes sure that a get_regimen function fails if the token is missing.";
		
		if (isset ($_POST['token']) ) unset($_POST['token']);
		$actual = $this->get_regimen();
		$expected = '{"result":-1}';	
		$this->unit->run($actual, $expected, $test_name, $notes);
		unset($_POST);
		$this->db->trans_complete();
	}
	
	private function test_get_regimen_invalid_token()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back

		$test_name = "test_get_regimen_invalid_token()";
		$notes = "<p>This method makes sure that a get_regimen function fails if the token is invalid.</p>";

		$_POST['token'] = 'ZZZ7031d3ad534445b8100d23b181de7';
		$actual = $this->get_regimen();
		$expected = '{"result":-1}';	
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		unset($_POST);
		$this->db->trans_complete();
	}
	
	private function test_clear_tokens_success()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back

		$test_name = "test_clear_tokens_success()";
		$notes = "This method checks that when the clear_tokens method receives the correct, pre-defined key, the method returns as a success.";

		$actual = $this->clear_tokens(CLEAR_KEY);
		$expected = TRUE;	
		$this->unit->run($actual, $expected, $test_name, $notes);

		$this->db->trans_complete();
	}
	
	private function test_clear_tokens_invalid_key()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back

		$test_name = "test_clear_tokens_invalid_key()";
		$notes = "This method checks that when the clear_tokens method receives an invalid key, the method fails.";

		$actual = $this->clear_tokens('asdf');
		$expected = FALSE;	
		$this->unit->run($actual, $expected, $test_name, $notes);
		
		$this->db->trans_complete();

	}
	
	private function test_login_success()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back

		$test_name = "test_login_success()";
		$notes = "This method checks that when a POST with a valid username and password is submitted, the correct corresponding user ID is returned.";

		$_POST['username'] = 'billybob@web.com';
		$_POST['password'] = 'braindead9';
		$actual = $this->login();

		$actual = json_decode($actual, TRUE);
		$actual = $actual['token'];		
		
		//$actual = $this->_isValidMd5($actual);
		$expected = TRUE;	
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		
		unset($_POST);
		$this->db->trans_complete();

	}

	private function test_login_missing_username()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back

		$test_name = "test_login_missing_username()";
		$notes = "This method checks that when a POST is made with the username missing, the login function fails.";
		
		if (isset ($_POST['username']) ) unset($_POST['username']);
		$_POST['password'] = md5('password');
		
		$actual = $this->login();
		$actual = json_decode($actual, TRUE);
		$actual = $actual['result'];		
		
		$expected = ERR_AUTH;	
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		
		unset($_POST);
		$this->db->trans_complete();

	}
	
	private function test_login_missing_password()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back

		$test_name = "test_login_missing_password()";
		$notes = "This method checks that when a POST is made with the password missing, the login function fails.";

		$_POST['username'] = 'un';
		
		if (isset ($_POST['password']) ) unset($_POST['password']);
		$actual = $this->login();
		
		$actual = json_decode($actual, TRUE);
		$actual = $actual['result'];		
		
		$expected = ERR_AUTH;	
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		
		unset($_POST);
		$this->db->trans_complete();

	}
	
	private function test_getUserID_success_62()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back
		$test_name = "test_getUserID_success_62()";
		$notes = "<p>This method checks that the correct ID (62) is returned given a username/password combo.</p>";

		$email = "billybob@web.com";
		$password = "braindead9";
		$actual = $this->getUserID($email, $password);
		$expected = "62";
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		unset($_POST);
		$this->db->trans_complete();
	}
	
	private function test_getUserID_success_63()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back
		$test_name = "test_getUserID_success_63()";
		$notes = "<p>This method checks that the correct ID (63) is returned given a username/password combo.</p>";

		$email = "jane@doe.com";
		$password = "password";
		$actual = $this->getUserID($email, $password);
		$expected = "63";
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		unset($_POST);
		$this->db->trans_complete();
	}
	
	private function test_getUserID_success_64()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back
		$test_name = "test_getUserID_success_64()";
		$notes = "<p>This method checks that the correct ID (64) is returned given a username/password combo.</p>";

		$email = "ada@lovelace.com";
		$password = "password";
		$actual = $this->getUserID($email, $password);
		$expected = "64";
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		unset($_POST);
		$this->db->trans_complete();
	}
	
	private function test_getUserID_success_65()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back
		$test_name = "test_getUserID_success_65()";
		$notes = "<p>This method checks that the correct ID (65) is returned given a username/password combo.</p>";

		$email = "linus@torvolds.com";
		$password = "password";
		$actual = $this->getUserID($email, $password);
		$expected = "65";
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		unset($_POST);
		$this->db->trans_complete();
	}
	
	private function test_getUserID_fail_inactive_66()
	{
		$this->db->trans_start(TRUE); // Test mode Query will be rolled back
		$test_name = "test_getUserID_fail_inactive_66()";
		$notes = "<p>This method checks that the correct ID (66) and a correct un/pw combo still returns in failure if the account is inactive.</p>";

		$email = "herman@hollerith.com";
		$password = "password";
		$actual = $this->getUserID($email, $password);
		$expected = "-1";
		
		$this->unit->run($actual, $expected, $test_name, $notes);
		unset($_POST);
		$this->db->trans_complete();
	}
	
}