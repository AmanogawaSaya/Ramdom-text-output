# Ramdom-text-output
The Big Project Homework for Data Structure Class
Question:
随机文本生成器（综合）      				 
【问题描述】

有一种基于马尔可夫链（Markov Chain）算法的随机文本生成方法，它利用任何一个现有的某种语言的文本（如一本英文小说），可以构造出由这个文本中的语言使用情况而形成的统计模型，并通过该模型生成的随机文本将具有与原文本类似的统计性质（即具有类似写作风格）。

该算法的基本原理是将输入看成是由一些互相重叠的短语构成的序列，其将每个短语分割为两个部分：一部分是由多个词构成的前缀，另一部分是只包含一个词的后缀。在生成文本时依据原文本的统计性质（即前缀确定的情况下，得到所有可能的后缀），随机地选择某前缀后面的特定后缀。在此，假设前缀长度为两个单词，则马尔可夫链（Markov Chain）随机文本生成算法如下：

设w1和w2为文本的前两个词

输出w1和w2

循环：

随机地选出w3，它是原文本中w1w2为前缀的后缀中的一个

输出w3

w1 = w2

w2 = w3

重复循环

 

下面将通过一个例子来说明该算法原理，假设有一个原文如下：

Show your flowcharts and conceal your tables and I will be mystified. Show your tables and your flowcharts will be obvious.

下面是上述原文的一些前缀和其后缀（注意只是部分）的统计：

前缀  后缀

Show your

flowcharts  tables

your flowcharts

and  will

flowcharts and

conceal

flowcharts willl

be

your tables

and  and

will be

mystified.  obvious.

be mystified.

Show

be obvious.

(end)

基于上述文本，按照马尔可夫链（Markov Chain）算法随机文本生成文本时，首先输出的是Show your，然后随机取出flowcharts或tables。如果为前者，则接下来的前缀就变成your flowcharts，而下一个后缀应该是and或will；如果为tables，则接下来的前缀就变成your tables，而下一个词就应该是and。这样继续下去，直到产生出足够多的输出，或在查找后缀时遇到了结束标志。

 

编写一个程序从文件中读入一个英文文本，利用马尔可夫链（Markov Chain）算法，基于文本中固定长度的短语的出现频率，生成一个最大单词数目不超过N的新文本到给定文件中。程序要求前缀词的个数为2，最大单词数目N由标准输入获得。

说明：

1.    为了得到更好的统计特性，在此标点符号等非字母字符（如’ “ . , ? – ()等）也被看成单词的一部分，即“words”和“words.”是不同的单词。因此，在此将“词”定义为由“空白界定的字符串”；

2.    对于同一个前缀的后缀按出现顺序排放（不管该后缀是否已存在）；

3.    在处理文本时，文件结束标志也将作为某一前缀的一个后缀，如上面示例（说明：在为文件最后两个前缀单词“be obvious.”读取后缀时，遇到文件结束，即其没有相应后缀，此时可用一个特殊标记来表示其后缀，如，可存储一个自定义的特殊串（如“(end)”）作为其后缀来表示当前状态，即文件结束）；

4.    对于某一前缀，按如下方式来随机选择其后缀（如果某一前缀只有一个后缀，将直接选择该后缀）：

n = (int)(rrand() * N);

在此N为某一前缀的所有后缀的总数，n为所确定的后缀在该前缀的后缀序列中的序号（从0开始计数，即n为0时选取第一个后缀，为1时选取第二个后缀，以此类推）。在此，随机数生成函数rrand()的定义如下：

double seed = 997;

double rrand()

{

       double lambda = 3125.0;

       double m = 34359738337.0;

       double r;

       seed = fmod(lambda*seed, m); //要包含头文件#include <math.h>

       r = seed / m;

    return r;

}

注意：为了保证运行结果的确定性，请务必使用本文提供的随机数生成函数。

在下面条件满足时文本生成结束：1）遇到后缀为文件结束标志；或2）生成文本的单词数达到所设定的最大单词数。在程序实现时，当读到文件（结束）尾时，可将一个特殊标志赋给后缀串suffix变量。


【输入形式】

开打当前目录下英文文本文件“article.txt”进行统计分析，并从标准输入中读入一个正整数作为生成文本时的最大单词数。

【输出形式】

将生成文本输出到当前目录下文件“markov.txt”中。单词间以一个空格分隔，最后一个单词后空格可有可无。


【样例输入】

若当前目录下文件article.txt中内容如下：

I will give you some advice about life.

Eat more roughage;

Do more than others expect you to do and do it pains;

Remember what life tells you;

do not take to heart every thing you hear.

do not spend all that you have.

do not sleep as long as you want;

Whenever you say "I love you", please say it honestly;

Whevever you say "I am sorry", please look into the other person's eyes;

Whenever you find your wrongdoing, be quick with reparation!

Whenever you make a phone call smil when you pick up the phone, because someone feel it!

Understand rules completely and change them reasonably;

Remember, the best love is to love others unconditionally rather than make demands on them;

Comment on the success you have attained by looking in the past at the target you wanted to achieve most;

In love and cooking, you must give 100% effort - but expect little appreciation.

从标准输入中输入的单词个数为：

1000


【样例输出】

当前目录下所生成的文件markov.txt中内容如下：

I will give you some advice about life. Eat more roughage; Do more than others expect you to do and do it pains; Remember what life tells you; do not take to heart every thing you hear. do not take to heart every thing you hear. do not spend all that you have. do not sleep as long as you want; Whenever you find your wrongdoing, be quick with reparation! Whenever you find your wrongdoing, be quick with reparation! Whenever you find your wrongdoing, be quick with reparation! Whenever you find your wrongdoing, be quick with reparation! Whenever you say "I am sorry", please look into the other person's eyes; Whenever you say "I am sorry", please look into the other person's eyes; Whenever you make a phone call smil when you pick up the phone, because someone feel it! Understand rules completely and change them reasonably; Remember, the best love is to love others unconditionally rather than make demands on them; Comment on the success you have attained by looking in the past at the target you wanted to achieve most; In love and cooking, you must give 100% effort - but expect little appreciation.


【样例说明】

按照本文介绍的马尔可夫链（Markov Chain）算法将生成相关输出文件。


【评分标准】

本题是一个综合性能测试题，其评分标准为在所有程序中运行最快的将得满分，其它程序的得分以最快的程序运行时间为基准，根据其运行时间计算得出。程序运行无结果或结果错误将不得分。

