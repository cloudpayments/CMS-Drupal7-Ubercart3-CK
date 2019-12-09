<?php

/**
 * Payment method callback: settings form.
 */
function cloudkassir_admin_settings() {
	$form = array();
	
	$aStatus = uc_order_status_options_list();

	$form['cloudkassir_inn'] = array(
		'#type' => 'textfield',
		'#title' => 'ИНН',
		'#default_value' => variable_get('cloudkassir_inn',''),
	);

	$form['cloudkassir_public_id'] = array(
		'#type' => 'textfield',
		'#title' => 'Public ID',
		'#default_value' => variable_get('cloudkassir_public_id',''),
	);
//
	$form['cloudkassir_api_password'] = array(
		'#type' => 'textfield',
		'#title' => 'Password for API',
		'#default_value' => variable_get('cloudkassir_api_password',''),
	);

	$form['cloudkassir_tax_system'] = array(
		'#type' => 'select',
		'#title' => 'Система налогообложения',
		'#default_value' => variable_get('cloudkassir_tax_system',0),
		'#options' => array(
			'0' => '0 — Общая система налогообложения',
			'1' => '1 — Упрощенная система налогообложения (Доход)',
			'2' => '2 — Упрощенная система налогообложения (Доход минус Расход)',
			'3' => '3 — Единый налог на вмененный доход',
			'4' => '4 — Единый сельскохозяйственный налог',
			'5' => '5 — Патентная система налогообложенияе'
		)
	);

	$form['cloudkassir_notice'] = array(
	    '#type' => 'fieldset',
        '#title' => "Для использования параметров НДС, отличного от 'брать из настроек', пожалуйста, убедитесь, что у вас отключены/удалены настройки налогов непосредственно в Ubercart.",
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
    );

	$form['cloudkassir_tax_product'] = array(
		'#type' => 'select',
		'#title' => 'Ставка налога для товаров',
		'#default_value' => variable_get('cloudkassir_tax_product',0),
		'#options' => array(
			'-1' => 'VAT Free',
			'0' => 'VAT 0%',
			'10' => 'VAT 10%',
			'20' => 'VAT 20%',
			'110' => 'VAT 10/110',
			'120' => 'VAT 20/120',
			'-2' => 'Брать из настроек'
		)
	);


	$form['cloudkassir_tax_shipping'] = array(
		'#type' => 'select',
		'#title' => 'Ставка налога для доставки',
		'#default_value' => variable_get('cloudkassir_tax_shipping',0),
		'#options' => array(
			'-1' => 'VAT Free',
			'0' => 'VAT 0%',
			'10' => 'VAT 10%',
			'20' => 'VAT 20%',
			'110' => 'VAT 10/110',
			'120' => 'VAT 20/120',
			'-2' => 'Брать из настроек'
		)
	);

	$form['cloudkassir_status_success'] = array(
		'#type' => 'select',
		'#title' => 'Заказ Оплачен',
		'#notice' => 'sdfsdfsdasd',
		'#default_value' => variable_get('cloudkassir_status_success',''),
		'#options' => $aStatus,
	);

	/**
	 * Способы оплаты для которых выписывать чек
	 */
	$aWayPayment = uc_payment_method_options_list();
	$form['cloudkassir_ways_payment'] = array(
		'#type' => 'select',
		'#multiple' => TRUE,
		'#title' => 'Выберите способы оплаты, для которых хотите включить отправку чеков',
		'#required' => FALSE,
		'#options' => $aWayPayment,
		'#size' => 5,
		'#weight' => 0,
		'#default_value' => variable_get('cloudkassir_ways_payment',[]),
	);


	
	return system_settings_form($form);
}