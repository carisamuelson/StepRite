<div class="content">
	<div class="left-box">
		<?php echo form_open('account/new_patient'); ?>
		
<table id="tables">
	<tr>
		<td class="left">Medical Record Number:</td>
		<td class="right"><input type="text" name="mrn" id="mrn" size="35" value="<?php echo set_value('mrn'); ?>" /></td>
	</tr>
	
	<tr>
		<td class="left">Patient's First Name:</td>
		<td class="right"><input type="text" name="first_name" id="first_name" size="35" value="<?php echo set_value('first_name'); ?>" /></td>
	</tr>
	
	<tr>
		<td class="left">Patient's Last Name:</td>
		<td class="right"><input type="text" name="last_name" id="last_name" size="35" value="<?php echo set_value('last_name'); ?>" /></td>
	</tr>
	
	<tr>
		<td class="left">Patient's Phone Number:</td>
		<td class="right"><input type="text" name="phone_num" id="phone_num" size="35" value="<?php echo set_value('phone_num'); ?>" /></td>
	</tr>
	
	<tr>
		<td class="left">Patient's Email:</td>
		<td class="right"><input type="text" name="email" id="email" size="35" value="<?php echo set_value('email'); ?>" /></td>
	</tr>

	<tr>
		<td class="left">Name of Patient's Rehabilitation Provider:</td>
		<td class="right"><input type="text" name="pt" id="pt" size="35" value="<?php echo set_value('pt'); ?>" /></td>
	</tr>
	
	<tr>
		<td class="left">Name of Patient's Doctor:</td>
		<td class="right"><input type="text" name="dr" id="dr" size="35" value="<?php echo set_value('dr'); ?>" /></td>
	</tr>

	<tr>
		<td class="left">Patient's Height in Inches:</td>
		<td class="right"><input type="text" name="height" id="height" size="3" value="<?php echo set_value('height'); ?>" /></td>
	</tr>
	
	<tr>
		<td class="left">Patient's Weight in Pounds:</td>
		<td class="right"><input type="text" name="weight" id="weight" size="3" value="<?php echo set_value('weight'); ?>" /></td>
	</tr>	
	
	<tr>
		<td class="left">Injured Leg:</td>
		<td class="right">
			<input type="radio" name="injured_leg" id="left" value="left" /> Left 
			<input type="radio" name="injured_leg" id="right" value="right" checked />Right
		</td >
	</tr>
	
	<tr>
		<td class="left">Daily frequency of exercises:</td>
		<td class="right">
			<select class="c-select" name="times">
				<option name="times" value="1">1 Time Per Day</option>
				<option name="times" value="2">2 Times Per Day</option>
				<option name="times" value="3" selected>3 Times Per Day</option>
				<option name="times" value="4">4 Times Per Day</option>
				<option name="times" value="5">5 Times Per Day</option>
				<option name="times" value="6">6 Times Per Day</option>
				<option name="times" value="7">7 Times Per Day</option>
				<option name="times" value="8">8 Times Per Day</option>
				<option name="times" value="9">9 Times Per Day</option>
			</select>
		</td>
	</tr>
	
	<tr>
		<td class="left">Treatment Start Date:</td>
		<td class="right"><input type="text" name="start_date" id="start_date" size="35" value="<?php echo set_value('start_date'); ?>" /></td>
	</tr>
	
	<tr>
		<td class="left">Treatment End Date:</td>
		<td class="right"><input type="text" name="end_date" id="end_date" size="35" value="<?php echo set_value('end_date'); ?>" /></td>
	</tr>

	<tr><td colspan="3"><hr /></td></tr>

	<tr><td colspan="3">Mandatory Pressure/Standing Protocol</td></tr>

	<tr>
		<td  class="left">Should the patient use a crutch:</td>
		<td class="right">
			<input type="radio" name="crutch_p" id="crutch_p1" value="yes"/>Yes 
			<input type="radio" name="crutch_p" id="crutch_p2" checked value="no"/>No
		</td>
	</tr>
	<tr>
		<td class="left">Pressure Percent:</td>
		
		<td class="right">
			<input type="text" name="pressure" id="pressure" size="3" value="<?php echo set_value('pressure'); ?>" style="background: none; border:0; font-weight:bold;" />
			<div id="pressure-slider" style="width:200px;"></div>
		</td>
</p>
	</tr>
	
	<tr><td colspan="3" style="padding: 20px 0px;"><hr /></td></tr>

	<tr>
		<td colspan="3">Mandatory Gait Protocol</td>
	</tr>
	<tr>
		<td class="left">Should the patient use a crutch:</td>
		<td class="right">
			<input type="radio" name="crutch_g" id="crutch_g1" value="yes"/>Yes 
			<input type="radio" name="crutch_g" id="crutch_g2" checked value="no"/>No
		</td>
	</tr>
	<tr>
	<td class="left">Walking:</td>
	<td>
		<select class="c-select">
			<option value="4">20 Steps</option>
			<option value="5">5 Minutes</option>
			<option value="6">10 Minutes</option>
			<option value="7">15 Minutes</option>
			<option value="8">30 Minutes</option>
			<option value="9">45 Minutes</option>
			<option value="10">1 Hour</option>
		</select>
	</td>
	</tr>

</table>
		
		
		<?php echo form_submit('submit','Register Patient');  ?>
		<?php echo form_close(); ?>
	</div>
</div>

<div class="content">
	<div class="right-box">
		<ul>
			<li><?php echo anchor('account/new_patient', 'Register New Patient'); ?></li>
			<?php /* <li><?php echo anchor('account/account/edit_information', 'Change Personal Information'); ?></li> */ ?>
			<li><?php echo anchor('account/change_password', 'Change Your Password'); ?></li>
		</ul>
	</div>
</div>


  </script>
  
<script>
	$(function() {
		$( "#start_date" ).datepicker({ dateFormat: 'yy-mm-dd' });
		$( "#end_date" ).datepicker({ dateFormat: 'yy-mm-dd' });
	});
	
	$(function() {
		$( "#pressure-slider" ).slider({
			orientation: "horizontal",
			min: 0,
			max: 100,
			step: 5,
			value: 50,
			slide: function( event, ui ) {
				$( "#pressure" ).val( ui.value );
			}
		});
		
		$( "#pressure" ).val( $( "#slider-vertical" ).slider( "value" ) );
	});	
</script>