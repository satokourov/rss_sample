<?php
//==================================================
// システム：RSSシステム
// 機能    ：RSSデータの取り込み処理（バッチ）
// 概要    ：
//==================================================

date_default_timezone_set('Asia/Tokyo');
mb_language('Japanese');
mb_internal_encoding('UTF-8');
require_once 'common.inc';
require_once 'models/getrss.inc';

// RSSデータを解析
$xml_data = simplexml_load_file(RSS_URL);

$data = array();
foreach ($xml_data->item as $item) {

	$xml = array();

	// XMLから基本情報を取得する
	$xml['link'] = (string)$item->link;
	$xml['title'] = (string)$item->title;
	$xml['description'] = (string)$item->description;
	$xml['date'] = date('Y-m-d H:i:s',strtotime((string)$item->children('http://purl.org/dc/elements/1.1/')->date));

	// URLからユーザ名・サーバ番号・エントリーNoを抽出する
	// URLのルールは下記とする
	$parse_url = parse_url($xml['link']);
	$pieces = explode(".", $parse_url['host']);
	//ユーザ名
	$xml['user_id'] = $pieces[0];
	//サーバ番号（番号が無い場合は「0」とする）
	preg_match("/[0-9]+/",$pieces[1],$match);
	$match[0] = (empty($match[0])) ? '99999' : $match[0];
	$xml['server_num'] = $match[0];
	//エントリーNo
	preg_match("/[0-9]+/",$parse_url['path'],$match);
	$xml['entry_num'] = $match[0];

	$data[] = $xml;
}

$cnt = importXMLData($data);
$msg = "[" . date("d-M-Y H:i:s") . "] RSSデータ取込[" . $cnt . "]件\n";
error_log($msg, 3, B_LOG);
