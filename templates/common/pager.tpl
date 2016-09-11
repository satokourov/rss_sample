{*
概要：ページャーを出力する
引数：pager Util::pagerの返値
      url 「?」か「&」で終わるリンク先
      page_name ページ番号の名前
*}

{if $pager.count > 0 && $pager.max_page > 1}
{strip}
	{if $pager.page > 1}
		<a href="{$url|default:'?'}{$page_name|default:'page'}={$pager.page-1}">&lt; 前へ</a>｜
	{/if}

	{section name=pager loop=$pager.end+1 start=$pager.start}
		{if $pager.page == $smarty.section.pager.index}
			{$smarty.section.pager.index}｜
		{else}
			<a href="{$url|default:'?'}{$page_name|default:'page'}={$smarty.section.pager.index}">{$smarty.section.pager.index}</a>｜
		{/if}
	{/section}

	{if $pager.page < $pager.max_page}
		<a href="{$url|default:'?'}{$page_name|default:'page'}={$pager.page+1}">次へ &gt;</a>
	{/if}
{/strip}
{/if}
