<?php
class Appservicemodel extends StepRite_Model
{

	function insert_rom($data)
	{
		 return $this->db->insert('romcalculations', $data); 
	}

	function insert_force($data)
	{
		 return $this->db->insert('forcecalculations', $data); 
	}

	function insert_gait($data)
	{
		 return $this->db->insert('sr_calc_gait', $data); 
	}
	
	function insert_activity($data)
	{
		 return $this->db->insert('activities', $data); 
	}
	
	function get_exercise_id_from_regimen_id($regimenID)
	{
		/*
		SELECT exercise_id FROM protcols
		WHERE protocols.id = $regimenID
		*/
		
		$this->db->select('exercise_id');
		$this->db->from('protocols');
		$this->db->where('protocols.id', $regimenID); 

		$query = $this->db->get();
		
		$result = $query->result_array();
		if ( $result == NULL ) $exercise_id = NULL;
		else $exercise_id = $result[0]['exercise_id'];
	
		return $exercise_id;	
	}
	
	function get_exercise_type_from_regimen_id($regimenID)
	{
		/*
		SELECT type 
		FROM protocols
		JOIN exercises ON protocols.exercise_id = exercises.id
		WHERE protocols.id = 69
		*/
		
		$this->db->select('type');
		$this->db->from('protocols');
		$this->db->join('exercises', 'protocols.exercise_id = exercises.id');
		$this->db->where('protocols.id', $regimenID); 

		$query = $this->db->get();
		
		$result = $query->result_array();
		if ( $result == NULL ) $exercise_type = NULL;
		else $exercise_type = $result[0]['type'];
	
		return $exercise_type;		
	}

	function get_regimen_count($regimenID)
	{
		/* SELECT count(protocol_id) as count FROM activities where patient_id = 1 AND protocol_id = 28 */
	
		$client_id = $this->get_regimen_owner($regimenID);
	
		$this->db->select('count(protocol_id) as count');
		$this->db->from('activities');
		$this->db->where('patient_id', $client_id); 
		$this->db->where('protocol_id', $regimenID); 

		$query = $this->db->get();
		
		$result = $query->result_array();
		if ( $result == NULL ) $regimen_count = NULL;
		else $regimen_count = $result[0]['count'];
		
		return $regimen_count;	
	}

	function get_regimen_owner($regimenID)
	{
		/* 
		SELECT patient_id
		FROM protocols
		WHERE protocols.id =69
		*/

		$this->db->select('patient_id');
		$this->db->from('protocols');
		$this->db->where('protocols.id', $regimenID); 

		$query = $this->db->get();
		
		$result = $query->result_array();
		if ( $result == NULL ) $regimen_owner = NULL;
		else $regimen_owner = $result[0]['patient_id'];
	
		return $regimen_owner;
	}
	
	function get_user_id_from_token($token)
	{		
		$this->db->select('patient_id');
		$this->db->from('tokens');
		$this->db->where('token', $token); 
		$query = $this->db->get();

		$result = $query->result_array();

		if ( $result == NULL ) $user_id = NULL;
		else $user_id = $result[0]['patient_id'];

		return $user_id;
	}
	
	function get_regimen($user_id)
	{
	
		/*
		select 

		protocols.id as RegimenID,
		protocols.exercise_id as ExerciseID,
		protocols.reps,
		protocols.hold_time,
		protocols.weight,
		exercises.isometric,
		exercises.name as ExerciseName,
		patients.times as timesPerDay

		from protocols

		join exercises ON protocols.exercise_id = exercises.id
		join users ON protocols.patient_id = users.id
		join patients ON users.id = patients.user_id

		WHERE protocols.patient_id = 62 AND protocols.active = 1
		*/
	
		$this->db->select('
		protocols.id as RegimenID,
		protocols.exercise_id as ExerciseID,
		protocols.reps,
		protocols.hold_time as hold,
		protocols.weight,
		exercises.isometric,
		exercises.name as ExerciseName,
		patients.times as timesPerDay');
		
		$this->db->from('protocols');
		$this->db->join('exercises', 'protocols.exercise_id = exercises.id');
		$this->db->join('users', 'protocols.patient_id = users.id');
		$this->db->join('patients', 'users.id = patients.user_id');
		
		$this->db->where('protocols.patient_id', $user_id);
		$this->db->where('protocols.active', "1"); 
		
		$query = $this->db->get();	
	
		return $query->result();
	}
	
	function clear_tokens()
	{
		return $this->db->empty_table('tokens') ? TRUE : FALSE;
	}
	
	function insert_token($data)
	{
		return $this->db->insert("tokens",$data) ? TRUE : FALSE ;
	}
}