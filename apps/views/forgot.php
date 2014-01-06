<div class="content">
	<div class="left-box">
		<?php echo form_open('forgot'); ?>
		<p>
			Email Address:
			<input type="text" size="35" id="email" name="email" value="<?php echo set_value('email'); ?>" />
		</p>
		<p>
			Captcha:
			<input type="text" size="35" id="captcha" name="captcha" /> 
			<?php echo $captcha['image']; ?>
		</p>
		<?php echo form_submit('submit','Submit');  ?>
		<?php echo form_close(); ?>
	</div>
</div>