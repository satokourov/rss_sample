<?php
//==================================================
// システム：RSSシステム
// 機能    ：DBクラス定義
// 概要    ：
//==================================================

require_once 'MDB2.php';
require_once 'define.inc';

//--------------------------------------------------
// 概要：DBクラス
//--------------------------------------------------
class Database {
	var $conn = null;

	//--------------------------------------------------
	// 概要：コンストラクタ
	//--------------------------------------------------
	function Database() {
		$this->conn = MDB2::connect(DB_DSN);
		if (MDB2::isError($this->conn)) {
			$this->conn = null;
			return;
		}

		$ret = $this->conn->setFetchMode(MDB2_FETCHMODE_ASSOC);
		if (MDB2::isError($ret)) {
			$this->conn->disconnect();
			$this->conn = null;
			return;
		}
	}

	//--------------------------------------------------
	// 概要：DBに接続できているかどうか
	// 返値：接続できているならtrue、それ以外はfalse
	//--------------------------------------------------
	function isValid() {
		return MDB2::isConnection($this->conn);
	}

	//--------------------------------------------------
	// 概要：SQLを実行し、実行結果を返す
	// 引数：sql SQL文
	//       prm プリペアに使用する配列
	//       is_manip trueにすると実行件数を得るが、代わりにexec()を使うこと
	// 返値：実行結果、失敗ならエラーオブジェクト
	//--------------------------------------------------
	function query($sql, $prm = null, $is_manip = false) {
		$stmt = $this->conn->prepare($sql, null, $is_manip ? MDB2_PREPARE_MANIP : MDB2_PREPARE_RESULT);
		if (MDB2::isError($stmt)) return $stmt;
		return $stmt->execute($prm);
	}

	//--------------------------------------------------
	// 概要：SQLを実行し、実行件数を返す
	// 引数：sql SQL文
	//       prm プリペアに使用する配列
	// 返値：実行件数、失敗ならエラーオブジェクト
	//--------------------------------------------------
	function exec($sql, $prm = null) {
		return $this->query($sql, $prm, true);
	}

	//--------------------------------------------------
	// 概要：SQLの実行結果を全件取得する
	// 引数：sql SQL文
	//       prm プリペアに使用する配列
	//       limit 取得件数
	//       offset 取得位置
	// 返値：成功でSELECT系ならデータ配列、それ以外はqueryと同じ
	//--------------------------------------------------
	function getAll($sql, $prm = null, $limit = null, $offset = null) {
		$ret = $this->conn->setLimit($limit, $offset);
		if (MDB2::isError($ret)) return $ret;

		$ret = $this->query($sql, $prm);
		if (!MDB2::isResult($ret)) return $ret;
		return $ret->fetchAll();
	}

	//--------------------------------------------------
	// 概要：SQLの実行結果を1件取得する
	// 引数：sql SQL文
	//       prm プリペアに使用する配列
	// 返値：成功でSELECT系ならデータ配列、それ以外はqueryと同じ
	//--------------------------------------------------
	function getRow($sql, $prm = null) {
		$ret = $this->query($sql, $prm);
		if (!MDB2::isResult($ret)) return $ret;
		return $ret->fetchRow();
	}

	//--------------------------------------------------
	// 概要：SQLの実行結果を1件の始めの項目を取得する
	// 引数：sql SQL文
	//       prm プリペアに使用する配列
	// 返値：成功でSELECT系ならデータ、それ以外はqueryと同じ
	//--------------------------------------------------
	function getOne($sql, $prm = null) {
		$ret = $this->query($sql, $prm);
		if (!MDB2::isResult($ret)) return $ret;
		return $ret->fetchOne();
	}

	//--------------------------------------------------
	// 概要：追加したIDを取得するが、失敗したらロールバックする
	// 引数：table テーブル名
	//       col 項目名
	// 返値：成功ならID、失敗ならfalse
	//--------------------------------------------------
	function getLastAddID($table = null, $col = null) {
		$id = $this->conn->lastInsertID($table, $col);
		if (MDB2::isError($id)) {
			$this->conn->rollback();
			return false;
		}
		return $id;
	}

	//--------------------------------------------------
	// 概要：トランザクションを開始する
	// 返値：成功ならtrue、それ以外はfalse
	//--------------------------------------------------
	function beginTran() {
		$ret = $this->conn->beginTransaction();
		return !MDB2::isError($ret);
	}

	//--------------------------------------------------
	// 概要：コミットするが、失敗したらロールバックする
	// 返値：成功ならtrue、それ以外はfalse
	//--------------------------------------------------
	function commit() {
		$ret = $this->conn->commit();
		if (MDB2::isError($ret)) {
			$this->conn->rollback();
			return false;
		}
		return true;
	}

	//--------------------------------------------------
	// 概要：ロールバックする
	//--------------------------------------------------
	function rollback() {
		$this->conn->rollback();
	}
};
