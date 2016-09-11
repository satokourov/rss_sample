<?php
//==================================================
// システム：RSSシステム
// 概要    ：
//==================================================

require_once 'database.inc';

//--------------------------------------------------
// 概要：RSSデータ登録
// 引数：data データ配列
// 返値：成功なら登録件数、それ以外はfalse
//--------------------------------------------------
function importXMLData(&$data) {

	if (!$GLOBALS['DB']->beginTran()) return false;

	$sql = "INSERT INTO rss_data (
				  link
				, title
				, description
				, date
				, user_id
				, server_num
				, entry_num
			) VALUES (?, ?, ?, ?, ?, ?, ?)";

	$cnt  = 0;
	foreach ( $data as $key=>$value ) {

		$same_data = checkSameData($value['link']);
		if ( empty($same_data) ) {

			$prm = array(
				  $value['link']
				, $value['title']
				, $value['description']
				, $value['date']
				, $value['user_id']
				, $value['server_num']
				, $value['entry_num']
			);

			$ret = $GLOBALS['DB']->exec($sql, $prm);
			if (MDB2::isError($ret) || $ret != 1) {
				$GLOBALS['DB']->rollback();
				return false;
			}
			$cnt++;
		}
	}

	if (!$GLOBALS['DB']->commit()) return false;
	return $cnt;
}

//--------------------------------------------------
// 概要：同一記事データの検索
// 引数：prm 
// 返値：成功なら登録件数
//--------------------------------------------------
function checkSameData(&$prm) {

	$sql = "SELECT COUNT(*) FROM rss_data WHERE link = ?";

	$data = $GLOBALS['DB']->getOne($sql, $prm);
	if (MDB2::isError($data)) $data = 0;

	return $data;
}
