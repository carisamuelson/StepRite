<div class="content">
	<div class="left-box">
			<?php echo form_open('login'); ?>
			<p>
				Email:
				<input type="text" size="35" id="email" name="email" value="<?php echo set_value('email'); ?>" />
				
				Password:
				<input type="password" size="35" id="password" name="password" />
				
				<?php echo form_submit('submit','Login');  ?>
				<?php echo form_close(); ?>
			</p>
			<p><br />
				Forgot your password? <a href="<?php echo base_url() . "forgot" ?>">Click Here</a><br />
				Want to use MedHab/StepRite to help better your patients? <a href="<?php echo base_url() . "register_provider" ?>"> Click here to register </a>
			</p>
	</div>
</div>

<div class="content">
	<div class="right-box">
		<h1>Press Releases</h1>
		<?php foreach($articles as $article) { ?>
		<p>
		<strong><?php echo $article['name']; ?></strong> - <?php echo $article['date']; ?><br />
		<?php echo $article['article']; ?>
		</p><br />
		<?php } ?>
	</div>
</div>