#Auto gen
$OnwerDir=[System.IO.Path]::GetDirectoryName($MyInvocation.MyCommand.Definition)
"#ifndef PHOENIX_WPEMOJI_RESOURCE_H`n#define PHOENIX_WPEMOJI_RESOURCE_H`n" > $OnwerDir\WPEmoji.h
"#include `"WPEmoji.h`"`n" >$OnwerDir\PhoWPEmoji.rc
### IDP_WPEMOJI_ID$NUM PNG 
For($i=1;$i -le 718;$i++)
{
$NumStr='{0:d3}' -f $i
$outstr="IDP_WPEMOJI_ID$NumStr PNG `"Images/WPEmoji/$NumStr.png`"`n"
$outstr >>$OnwerDir\PhoWPEmoji.rc
"#define IDP_WPEMOJI_ID$NumStr 3$NumStr " >>$OnwerDir\WPEmoji.h
}

"#endif `n" >>$OnwerDir\WPEmoji.h