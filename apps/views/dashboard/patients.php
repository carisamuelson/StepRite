<div class="grids">
	<div class="row">
		<div>Name</strong></div>
		<div>MRN</div>
		<div>Height</strong></div>
		<div>Weight</strong></div>
		<div>Doctor</div>
		<div></div>
	</div>	
<?php foreach($patients->result_array() as $row) { ?>	 
	<div class="row">
		<div><?php echo $row['last_name'] . ", " . $row['first_name']; ?></div>
		<div><?php echo $row['mrn']; ?></div>
		<div><?php echo $row['height']; ?></div>
		<div><?php echo $row['weight']; ?></div>
		<div><?php echo $row['dr']; ?></div>
		<div><a class="toggle-edit anchor" id="<?php echo $row['user_id']; ?>">Edit Patient</a></div>
	</div>
	
	<div class="edit-form <?php echo $row['user_id']; ?> ui-corner-bottom">
		<div class="form-elements<?php echo $row['user_id']; ?>">
			<?php echo form_open('dashboard/patients/edit', array('class' => 'edit' . $row['user_id'])); ?>
				<strong>Extend Patient Treatment Date</strong><br/><br/>
				<Treatment Start Date: <?php echo $row['start_date']; ?> <br/><br/>
				Initial Treatment End Date: <?php echo $row['end_date']; ?><br/><br/>
				Select a date to extend treatment to: <input type="text" name="extended_date" class="extended_date" size="10" value="<?php echo set_value('extended_date'); ?>" /> Format: YYYY-MM-DD <br/><br/> 
				The Treatment End Date for this patient is <strong><?php echo floor((strtotime($row['end_date']) - time()) / 86400); ?></strong> days away.<br/><br/>
				
				<input type="hidden" name="id" value="<?php echo $row['user_id'] ?>"/>
				<a class="update button" id="<?php echo $row['user_id'];?>">Update Patient</a>
				
			<?php echo form_close(); ?>
		</div>
		
		<div class="form-buttons" style="padding: 20px; text-align: center">
			<a class="toggle-edit anchor" id="<?php echo $row['user_id']; ?>">Close this window</a>
		</div>
	</div>
<?php } ?>
</div>

<script><!--
$(document).ready(function() {
	// initially hide the edit patient form for each patient
	$(".edit-form").hide();
	// toggle the hidden edit patient form on and off
	$(".toggle-edit").click(function() {
		var id = $(this).attr('id');
			if ($('.edit-form.' + id).is(':visible')) {
				$('.edit-form.' + id).slideUp("slow");
				
				var current_index = $("#tabs").tabs("option","active"); 
				$("#tabs").tabs('load',current_index);
			}
			else {
				$('.edit-form.' + id).slideDown(1000);
			}
	});
	// Update function
	$('.update').click(function() {
		var id = $(this).attr('id');
		$.ajax({
			type: "POST",
			url: "<?php echo base_url() . "dashboard/patients/edit" ?>",
			data: $('.edit' + id).serialize(),
			success: function(data) {
				if(data == "error") {
					$( '.form-elements' + id ).append("<br /><br /><span class=\"error\">A valid date is required</span>");
				}
				else {
					$( '.form-elements' + id ).html(data);
				}
			},
			error: function(data) {
				$( '.form-elements' + id ).append("<span class=\"error\">Unable to update the patient</span>")
			}
		});
	});
	// DatePicker
	$('.extended_date').each(function(){
		$(this).datepicker({ dateFormat: 'yy-mm-dd' });
});
});
</script>