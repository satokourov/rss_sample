<?php
//==================================================
// システム：RSSシステム
// 概要    ：
//==================================================

require_once 'database.inc';

//--------------------------------------------------
// 概要：表画面用の一覧取得
// 引数：search 検索条件配列
//       cnt_flg trueにすると取得件数を返す
// 返値：cnt_flg=trueなら取得件数、それ以外はデータ配列
// 備考：
//--------------------------------------------------
function getRssList(&$search, $cnt_flg) {
	$prm = array();

	if ($cnt_flg) {
		$sql = 'SELECT COUNT(*) ';
	} else {
		$sql = 'SELECT * ';
	}
	$sql .= 'FROM rss_data ';

	//日付
	if ( !empty($search['date']) ) {
		$where = (empty($where)) ? 'WHERE' : 'AND';
		$sql .= $where . ' (date >= ? AND date <= ?) ';
		$prm[] = $search['date'] . ' 00:00:00';
		$prm[] = $search['date'] . ' 23:59:59';
	}
	//URL
	if ( !empty($search['link']) ) {
		$where = (empty($where)) ? 'WHERE' : 'AND';
		$sql .= $where . ' link = ? ';
		$prm[] = $search['link'];
	}
	//ユーザ名
	if ( !empty($search['user_id']) ) {
		$where = (empty($where)) ? 'WHERE' : 'AND';
		$sql .= $where . ' user_id = ? ';
		$prm[] = $search['user_id'];
	}
	//サーバ番号
	if ( !empty($search['server_num']) ) {
		$where = (empty($where)) ? 'WHERE' : 'AND';
		$sql .= $where . ' server_num = ? ';
		$prm[] = $search['server_num'];
	}
	//エントリーNo
	if (!empty($search['from_entry_num']) && !empty($search['to_entry_num'])) {
		$where = (empty($where)) ? 'WHERE' : 'AND';
		$sql .= $where . ' (entry_num >= ? AND  entry_num <= ?) ';
		$prm[] = $search['from_entry_num'];
		$prm[] = $search['to_entry_num'];
	}
	if (!empty($search['from_entry_num']) && empty($search['to_entry_num'])) {
		$where = (empty($where)) ? 'WHERE' : 'AND';
		$sql .= $where . ' entry_num >= ? ';
		$prm[] = $search['from_entry_num'];
	}
	if (empty($search['from_entry_num']) && !empty($search['to_entry_num'])) {
		$where = (empty($where)) ? 'WHERE' : 'AND';
		$sql .= $where . '  entry_num <= ? ';
		$prm[] = $search['to_entry_num'];
	}
	//ブログタイトル
	if ( !empty($search['title']) ) {
		$where = (empty($where)) ? 'WHERE' : 'AND';
		$sql .= $where . ' title LIKE ? ';
		$prm[] = Util::convLikeSQL($search['title']);
	}

	if ($cnt_flg) {
		// 件数
		$data = $GLOBALS['DB']->getOne($sql, $prm);
		if (MDB2::isError($data)) $data = 0;
	} else {
		// データ配列
		$sql .= ' ORDER BY date DESC';
		$data = $GLOBALS['DB']->getAll($sql, $prm, $search['limit'], $search['offset']);
		if (MDB2::isError($data)) $data = array();
	}

	return $data;
}
