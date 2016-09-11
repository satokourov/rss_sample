<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>RSSシステム</title>
<link href="common/css/common.css" rel="stylesheet" type="text/css" />
<link href="common/css/jquery-ui.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="common/js/jquery.min.js"></script>
<script type="text/javascript" src="common/js/jquery-ui.min.js"></script>
<script type="text/javascript" src="common/js/jquery.ui.datepicker-ja.js"></script>
<script type="text/javascript" src="common/js/jquery.numeric.js"></script>
<script type="text/javascript">
<!--
{literal}
$(document).ready(function(){    //カレンダー
	jQuery('.jquery-ui-datepicker').datepicker({
		showOn: "button",
		buttonImage: "common/img/icon_schedule.gif",
		buttonImageOnly: true,
		buttonText: "カレンダー"
	});
});
{/literal}
// -->
</script>
</head>
<body>
<div class="wrapper">
	<div class="header">
		<div class="headerInner">
			<h1 class="hLogo left">RSSシステム</h1>
		</div>
		<ul class="gMenu">
			<li><a href="">検索・一覧</a></li>
		</ul>
	</div>
	<div class="contents">
	{include file='common/error.tpl' err=$err}

		<div class="section">
			<form action="./" method="post">
				<table border="0" class="table01">
					<tr>
						<th>日付</th>
						<td>
							<input type="text" name="date" value="{$search_cond.date}" class="formText01 wd200  jquery-ui-datepicker" maxlength="255" />&nbsp;&nbsp;※完全一致
						</td>
						<th>URL</th>
						<td>
							<input type="text" name="link" value="{$search_cond.link}" class="formText01 wd410" maxlength="255" />&nbsp;※完全一致
						</td>
					</tr>
					<tr>
						<th>ユーザ名</th>
						<td>
							<input type="text" name="user_id" value="{$search_cond.user_id}" class="formText01 wd200" maxlength="255" />&nbsp;※完全一致
						</td>
						<th>ブログタイトル</th>
						<td>
							<input type="text" name="title" value="{$search_cond.title}" class="formText01 wd410" maxlength="255" />&nbsp;※部分一致
						</td>
					</tr>
					<tr>
						<th>サーバ番号</th>
						<td>
							<input type="text" name="server_num" value="{$search_cond.server_num}" class="formText01 wd100 numeric antirc" maxlength="10" />&nbsp;※完全一致（数値のみ。サーバ番号無しは「99999」）
						</td>
						<th>エントリーNo</th>
						<td>
							<input type="text" name="from_entry_num" value="{$search_cond.from_entry_num}" class="wd100 formText01 numeric antirc" maxlength="10" />
							&nbsp;～&nbsp;
							<input type="text" name="to_entry_num" value="{$search_cond.to_entry_num}" class="wd100 formText01 numeric antirc" maxlength="10" />&nbsp;※片方のみ指定可能（数値のみ）
						</td>
					</tr>
				</table>
				<p class="aligncenter mt20">
					<button type="submit" name="sc" value="1" class="button buttonColorSwitch">検索</button>&nbsp;
					<button type="submit" name="reset" value="1" class="button buttonColorReset">検索条件をリセット</button>
				</p>
			</form>
		</div>

		<div class="section">
			<p class="pagination left">
			<span>[{$pager.count}件]</span>
			{if $pager.count > 0 && $pager.max_page > 1}
				{include file='common/pager.tpl' pager=$pager}
			{/if}
			</p>

			<table class="table02" border="0">
				<tr>
					<th>日付</th>
					<th>タイトル</th>
					<th>description</th>
				</tr>
				{if $pager.count > 0}
					{foreach from=$data_list|smarty:nodefaults item=data name=dialogue}
					<tr>
						<td>{$data.date}</td>
						<td style="word-break: break-all;"><a href="{$data.link}" target="_blank">{$data.title}</a></td>
						<td style="word-break: break-all;">{$data.description}</td>
					</tr>
					{/foreach}
				{else}
				<tr>
					<td colspan="3">結果が0件でした</td>
				</tr>
			{/if}
			</table>

			<p class="pagination left mt20">
			<span>[{$pager.count}件]</span>
			{if $pager.count > 0 && $pager.max_page > 1}
				{include file='common/pager.tpl' pager=$pager}
			{/if}
			</p>
		</div>
	</div>

	<div class="footer">
		<p class="pagetop"><a href="#top">ページの先頭へ</a></p>
		<address>
		Copyright (C) *****. All rights reserved.
		</address>
	</div>
</div>

{literal}
<script type="text/javascript">
	// 数値
	$(".numeric").numeric();
	// *「右クリック貼り付け」対応
	$(".antirc").change(function() {
	  $(this).keyup();
	});
</script>
{/literal}
</body>
</html>
