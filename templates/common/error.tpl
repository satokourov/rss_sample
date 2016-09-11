{*
概要：エラーがあればエラーメッセージを出力する
引数：err エラー配列
*}

{if $err != null}
	<div class="txtMsg msgError">
	{foreach from=$err item=err_msg}
		{$err_msg}<br />
	{/foreach}
	</div>
{/if}
