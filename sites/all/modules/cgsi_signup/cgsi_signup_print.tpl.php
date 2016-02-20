<?php
/**
 * @file
 * Display a printable invoice for users to print/mail their application
 * to CGSI.
 *
 * Laregely copied from ubercart.module's invoice template.
 */
?>

<?php
// Message gets displayed if user has products in their cart.
if (count(uc_cart_get_contents())): ?>
<div class="message warning">
	<p>The pay-by-mail option is available only for membership applications
		and renewals. You may print this receipt and send it with payment for
		your membership.</p>
	<p>
		Please proceed to the online <a href="<?php print url('cart'); ?>">checkout</a>
		to pay for the other items in your shopping cart.
	</p>
</div>
<?php endif; ?>

<p>Print this page, complete your payment information and mail to:</p>

<table width="95%" border="0" cellspacing="0" cellpadding="1"
	align="center" bgcolor="#1c5124"
	style="font-family: verdana, arial, helvetica; font-size: small;">
	<tr>
		<td>
			<table width="100%" border="0" cellspacing="0" cellpadding="5"
				align="center" bgcolor="#FFFFFF"
				style="font-family: verdana, arial, helvetica; font-size: small;">
				<tr valign="top">
					<td>
						<table width="100%"
							style="font-family: verdana, arial, helvetica; font-size: small;">
							<tr>
								<td><img src="../../sites/all/themes/cgsi/images/cgsi_tree.gif" />
								</td>
								<td></td>
								<td nowrap="nowrap"><?php print uc_store_address(); ?><br /> <?php print variable_get('uc_store_phone', ''); ?>
								</td>
							</tr>
						</table>
					</td>
				</tr>

				<tr valign="top">
					<td>

						<table cellpadding="4" cellspacing="0" border="0" width="100%"
							style="font-family: verdana, arial, helvetica; font-size: small;">

							<tr>
								<td>Membership Price:</td>
								<td><?php print $product->title; ?> $<?php print money_format('%i', $product->sell_price); ?>
								</td>
							</tr>

							<tr>
								<td>Type:</td>
								<td><?php print ($account->renew == 1) ? 'Renewal' : 'New'; ?></td>
							</tr>

							<?php if($donation_amount): ?>
							<tr>
								<td>Donations:</td>
								<td><?php print money_format('%i', $donation_amount); ?></td>
							</tr>
							<?php endif; ?>

							<tr>
								<td nowrap="nowrap"><b><?php echo t('Order Grand Total:'); ?> </b>
								</td>
								<td width="98%"><b>$<?php print money_format('%i', $grand_total); ?>
								</b>
								</td>
							</tr>

							<tr>
								<td colspan="2" bgcolor="#1c5124" style="color: white;"><b><?php echo t('Account Summary:'); ?>
								</b>
								</td>
							</tr>

							<tr>
								<td colspan="2"><?php
								print '<table width="100%" style="font-family: verdana, arial, helvetica; font-size: small;">';
								print '<tr><td>First Name:</td><td>' . check_plain($account->profile_first_name) . '</td></tr>';
								print '<tr><td>Last Name:</td><td>' . check_plain($account->profile_last_name) . '</td></tr>';
								print '<tr><td>2nd Household Member First Name:</td><td>' . check_plain($account->profile_first_name_2) . '</td></tr>';
								print '<tr><td>2nd Household Member Last Name:</td><td>' . check_plain($account->profile_last_name_2) . '</td></tr>';
								print '<tr><td>Email Address:</td><td>' . check_plain($account->mail) . '</td></tr>';
								print '<tr><td>Address:</td><td>' . check_plain($account->profile_address_1) . '</td></tr>';
								print '<tr><td>Address:</td><td>' . check_plain($account->profile_address_2) . '</td></tr>';
								print '<tr><td>City:</td><td>' . check_plain($account->profile_city) . '</td></tr>';
								print '<tr><td>State/Province:</td><td>' . check_plain($account->profile_state) . '</td></tr>';
								print '<tr><td>Zip/Postal Code:</td><td>' . check_plain($account->profile_zipcode) . '</td></tr>';
								print '<tr><td>Country:</td><td>' . check_plain($account->profile_country) . '</td></tr>';
								print '<tr><td>Phone:</td><td>' . check_plain($account->profile_phone) . '</td></tr>';
								print '<tr><td>Former CGSI member?:</td><td>' . check_plain($account->profile_former_member) . '</td></tr>';
								print '<tr><td>Former CGSI member number:</td><td>' . check_plain($account->profile_former_member_number) . '</td></tr>';
								print '<tr><td>How did you hear about CGSI:</td><td>' . check_plain($account->profile_heard_about) . '</td></tr>';
								print '<tr><td>Other:</td><td>' . check_plain($account->profile_heard_about_other) . '</td></tr>';
								print '<tr><td>Membership Level:</td><td>' . check_plain($account->profile_membership_level) . '</td></tr>';
								print '<tr><td>Membership term:</td><td>' . check_plain($account->profile_membership_term) . '</td></tr>';
								print '<tr><td>Membership price:</td><td>$' . round($product->sell_price) . '</td></tr>';
								print '</table>';
								?>
								</td>
							</tr>

							<tr>
								<td colspan="2" bgcolor="#1c5124" style="color: white;"><b><?php echo t('Payment information:'); ?>
								</b>
								</td>
							</tr>

							<tr>
								<td colspan="2">

									<p>
										<strong>Billing Address:</strong>
									</p>
									<p>
										<span
											style="display: block; float: left; width: 10px; height: 10px; margin-right: 8px; border: 1px solid #000;"></span>
										Use same address as above.
									</p>
									<p>Name: _____________________________________</p>
									<p>Address: _____________________________________</p>
									<p>Address2: _____________________________________</p>
									<p>City: _____________________________________</p>
									<p>State/Province: _____________________________________</p>
									<p>Zip/Postal Code: _____________________________________</p>
									<p>
										<span
											style="display: block; float: left; width: 10px; height: 10px; margin-right: 8px; border: 1px solid #000;"></span>
										My check is enclosed. Make checks payable to CGSI.
									</p>
									<p>
										<span
											style="display: block; float: left; width: 10px; height: 10px; margin-right: 8px; border: 1px solid #000;"></span>
										Bill my credit card<br />
										&nbsp;&nbsp;&nbsp;&nbsp;#:_____________________________________<br />
										&nbsp;&nbsp;&nbsp;&nbsp;Exp. Date ____________
									</p>
								</td>
							</tr>

							<tr>
								<td colspan="2" bgcolor="#1c5124" style="color: white;"><b><?php echo t('Surnames you are researching:'); ?>
								</b>
								</td>
							</tr>

							<tr>
								<td colspan="2">
									<p>CGSI has been collecting member surnames for years, along
										with data on the village, town, or district of origin. This
										surname information will soon be available to members on our
										website. By using this resource, you may be able to locate
										long-lost relatives locally or in their ancestral area. You
										may submit as many names as you wish and please update them as
										new names are found or if you find that corrections need to be
										made.</p>
									<p>
										<strong>CGSI Disclaimer:</strong> By entering your surnames
										into this database, you are granting access to your home
										address and email address to fellow members whose own search
										results in a hit on one of our names. Sharing contact info
										with fellow members is necessary to determine any
										relationship.
									</p>
									<p>Once a membership is activated, the member can enter
										surnames directly into the My Surnames section on our website
										(preferred method). Another option is to enter them below.</p>
								</td>
							</tr>

							<tr>
								<td colspan="2">
									<table width="100%" cellpadding="12"
										style="border: 1px solid #000">
										<tr>
											<td><strong>Surname</strong></td>
											<td><strong>European City/County</strong></td>
											<td><strong>European Country</strong></td>
											<td><strong>Immigratin area (US or other)</strong></td>
										</tr>
										<tr>
											<td style="border: 1px solid #000">e.g. Dvorak</td>
											<td style="border: 1px solid #000">Brno</td>
											<td style="border: 1px solid #000">Moravia</td>
											<td style="border: 1px solid #000">Spillville IA</td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
										<tr style="height: 24px">
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
											<td style="border: 1px solid #000"></td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>

<div align="right" style="margin-top: 1em; margin-right: 1em;">
	<input type="button" value="<?php print t('Print application'); ?>"
		onclick="window.print();" />
	<?php print l('Home Page', '<front>'); ?>
</div>
