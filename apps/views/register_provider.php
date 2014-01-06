<div class="content">
	<div class="left-box">
		<?php echo form_open('register_provider'); ?>
		
		First Name:
		<input type="text" size="35" id="first_name" name="first_name" value="<?php echo set_value('first_name'); ?>" />
		
		Last Name:
		<input type="text" size="35" id="last_name" name="last_name" value="<?php echo set_value('last_name'); ?>" />
		
		National Provider Identification Number:
		<input type="text" size="35" id="npin" name="npin" value="<?php echo set_value('npin'); ?>" />
		
		Business Name:
		<input type="text" size="35" id="business_name" name="business_name" value="<?php echo set_value('business_name'); ?>" />
		
		Business Address:
		<input type="text" size="35" id="business_address" name="business_address" value="<?php echo set_value('business_address'); ?>" />
		
		Phone Number:
		<input type="text" size="35" id="phone_num" name="phone_num" value="<?php echo set_value('phone_num'); ?>" />
		
		Cellular Phone Number:
		<input type="text" size="35" id="cell_num" name="cell_num" value="<?php echo set_value('cell_num'); ?>" />
		
		Email Address:
		<input type="text" size="35" id="email" name="email" value="<?php echo set_value('email'); ?>" />

		Password:
		<input type="password" size="35" id="password" name="password" value="<?php echo set_value('password'); ?>" />
		
		Confirm Password:
		<input type="password" size="35" id="confirm_password" name="confirm_password" value="<?php echo set_value('confirm_password'); ?>" />
		
		Captcha:
		<input type="text" size="35" id="captcha" name="captcha" /> 
		<?php echo $captcha['image']; ?>
		
		<br /><br />
		<?php echo form_submit('submit','Register');  ?>
		<?php echo form_close(); ?>
	</div>
</div>
<div class="content">
	<div class="right-box">
		<h2>Our Solutions</h2>
		Our StepRite Solution is a breakthrough technology to help orthopedic 
		surgeons evaluate patient’s pre and post surgery. It was designed 
		to improve rehab with measurable evidence, leading to better and 
		faster outcomes.
	</div>
</div>