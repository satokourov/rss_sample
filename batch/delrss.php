<?php
//==================================================
// システム：RSSシステム
// 機能    ：3日以上前のRSSデータを削除する（バッチ）
// 概要    ：
//==================================================

date_default_timezone_set('Asia/Tokyo');
mb_language('Japanese');
mb_internal_encoding('UTF-8');
require_once 'common.inc';
require_once 'models/delrss.inc';

deleteXMLData();
$msg = "[" . date("d-M-Y H:i:s") . "] RSSデータ削除処理実行\n";
error_log($msg, 3, B_LOG);
