#!/bin/bash

help()
{
cat << _END_
judge.sh [プログラム] [インプットファイル] [出力ファイル名] [比較対象の答えファイル]
	プログラムを実行したあと、結果をdiffを用いて比較します。
	例）
		./judge.sh ./a.out A out A.ans

judge.sh -h
	ヘルプを表示します。
_END_
}

#ヘルプ表示
if [ $1 = "-h" ] ; then
	help
	exit 0
fi

#引数チェック
if [ $# != 4 ] ; then
	echo "引数の数が一致しません。"
	help
	exit 1
fi

if ! [ -e $1 -a -e $2 -a -e $4 ] ; then
	echo "存在しないファイル名を指定しています。"
	exit 1
fi


#実行
if [ -x $1 ] ; then
	$1 < $2 > $3
else
	echo $1" は実行可能ではありません。"
	exit 1
fi

#比較
DIF=`diff $3 $4`
if [ -z `echo ${DIF} | awk 'NR==1{printf $1}'` ] ; then
	echo "Correct Answer !"
else
	DIFNO=$( echo ${DIF} | awk -F "," 'NR==1{ print $1 }' | awk -F "c" '{ print $1 }' )
	diff $3 $4 | awk 'NR<=2{ print $0 } F==1{ print $0; F=2 } F==0{ if( $0 == "---" ){ print $0; F=1 } }' | cat
	echo "Wrong Answer on line" ${DIFNO} "."
fi

