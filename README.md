<div class="WordSection1">

<span class="SpellE">Pluvi.On</span>

Contexto:

Como bons paulistanos, passamos pela mesma situação todos os anos. Chega
dezembro, o céu escurece, a gente ouve um trovão lá no fundo, já dá
aquele gelo na espinha <span class="SpellE">pq</span> a gente sabe que
vem uma tempestade e provavelmente uma enchente por aí... E esse tipo de
problema não acontece só em SP. Se olharmos Brasil, existem
aproximadamente 30 milhões de brasileiros expostos ao risco de enchentes
e inundações. Além disso, existe uma projeção de impacto financeiro,
onde as potenciais perdas anuais podem chegar a 4 bilhões de dólares até
2030 (Fonte: <span class="SpellE">Swiss</span> Re)

Olhando pra esse cenário alarmante, pensamos: “Será que não existe
nenhuma tecnologia de amplo acesso que possa resolver esse <span
class="GramE">problema?”</span> Se não para resolver totalmente, pelo
menos entregar mais informação, mais inteligência para que a população
possa se prevenir nesses eventos?

Resolvemos juntar nosso humilde conhecimento de hardware e software e
mergulhamos nesse mundo e logo de cara demos de cara com uma barreira:
as dificuldades de conseguir informações sobre clima e chuva

Identificamos 3 principais desafios relacionados à informação:

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">1)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>As informações históricas são de difícil acesso ao
cidadão comum (ou estão em mão de instituições privadas ou demandam
muita burocracia dos órgãos públicos)

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">2)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>Muitas delas são coletadas apenas no dia seguinte e
não auxiliam na prevenção

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">3)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>São informadas de forma genérica: “pode alagar a
cidade de SP” – mas SP é grande demais para termos apenas essa
informação. A probabilidade de alagar a Av. Paulista é sempre muito
menor do que alagar a Av. Aricanduva

Foi a partir dessas hipóteses que construímos o <span
class="SpellE">Pluvi.On</span>, uma estação meteorológica Open <span
class="SpellE">Source</span> e de baixo custo para ser espalhada na
maior quantidade de pontos da cidade que pudermos!!! Chega de <span
class="SpellE">blá</span> <span class="SpellE">blá</span> <span
class="SpellE">blá</span> e vamos ao que interessa:

Escolhemos o ESP8266 como “cérebro” da operação, por que?

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">1)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>É barato! Dá para comprar uma peça sem <span
class="SpellE">breakout</span> por uns R\$20 e na sua forma mais
completa (<span class="SpellE">NodeMCU</span>) por uns R\$50

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">2)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>Já tem <span class="SpellE">wifi</span> embutido!
Isso facilita o envio das informações em tempo real

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">3)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>Tem um monte de I/O e pode ser programado <span
class="SpellE">na</span> IDE do <span class="SpellE">Arduino</span>

+--------------------------------------+--------------------------------------+
| <span                                | <span                                |
| style="mso-fareast-language:PT-BR;   | style="mso-fareast-language:PT-BR;   |
|   mso-no-proof:yes">![Resultado de   |   mso-no-proof:yes">![Resultado de   |
| imagem para esp8266                  | imagem para                          |
| esp-12e](github_md_arquivos/image002 | nodemcu](github_md_arquivos/image004 |
| .jpg){width="251"                    | .jpg){width="252"                    |
| height="189"}</span>                 | height="189"}</span>                 |
+--------------------------------------+--------------------------------------+
| ESP8266 ESP12-e                      | <span class="SpellE">NodeMCU</span>  |
+--------------------------------------+--------------------------------------+

 

Hoje estamos utilizando apenas 3 sensores, o DHT22 para temperatura e
umidade, um sensor hall A3144 para medir quantidade e intensidade de
chuva e um sensor de chuva para avaliar precisamente quando a chuva
começou.

Fotos:

+-------------------------+-------------------------+-------------------------+
| <span                   | <span                   | <span                   |
| style="mso-fareast-lang | style="mso-fareast-lang | style="mso-fareast-lang |
| uage:PT-BR;             | uage:PT-BR;             | uage:PT-BR;             |
|   mso-no-proof:yes">![R |   mso-no-proof:yes">![R |   mso-no-proof:yes">![R |
| esultado                | esultado                | esultado                |
| de imagem para          | de imagem para          | de imagem para sensor   |
| dht22](github_md_arquiv | a3144](github_md_arquiv | de                      |
| os/image006.jpg){width= | os/image008.jpg){width= | chuva](github_md_arquiv |
| "189"                   | "203"                   | os/image010.jpg){width= |
| height="189"}</span>    | height="203"}</span>    | "189"                   |
|                         |                         | height="189"}</span>    |
+-------------------------+-------------------------+-------------------------+
| <span                   | <span                   | <span                   |
| style="mso-fareast-lang | style="mso-fareast-lang | style="mso-fareast-lang |
| uage:PT-BR;             | uage:PT-BR;             | uage:PT-BR;             |
|   mso-no-proof:yes">DHT |   mso-no-proof:yes">A31 |   mso-no-proof:yes">Sen |
| 22</span>               | 44</span>               | sor                     |
|                         |                         | de Chuva</span>         |
+-------------------------+-------------------------+-------------------------+

 

Esquema <span class="SpellE">Fritzing</span>:

<span
style="mso-fareast-language:PT-BR;mso-no-proof:yes">![](github_md_arquivos/image012.png){width="375"
height="420"}</span>

O esquema é bastante simples, o DHT22 envia informações de 30 em 30 min,
isso garante para gente um “<span class="SpellE">Dead</span> <span
class="SpellE">man</span> <span class="SpellE">button</span>” da estação
e temos certeza que ela está funcionando. O sensor hall funciona
contando “voltas” do <span class="SpellE">tipping</span> <span
class="SpellE">bucket</span> que é uma estrutura utilizada em diversos
pluviômetros profissionais, olhando o desenho já dá para entender como
funciona! E para que raios usamos o sensor de chuva??? Bom, esse sensor
surgiu depois quando notamos que a intensidade da chuva é um fator
fundamental e a única forma de saber exatamente quando uma chuva começa
é com as primeiras gotas de chuva. Pode ser um <span
class="GramE">preciosismo</span> mas por que não?

<span style="mso-fareast-language:PT-BR;mso-no-proof:yes">![Resultado de
imagem para tipping bucket
gif](github_md_arquivos/image014.jpg){width="301" height="189"}</span>

O sensor de chuva tem outra função interessante, estamos ligando-o em
uma interrupção e a ideia é que ele sirva para “acordar” o ESP8266.

Desafios e ajuda que precisamos no momento:

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">1)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>Ainda estamos brigando com a forma de alimentar as
estações. Não chegamos a uma conclusão ainda: bateria recarregável,
pilhas, fonte AC, <span class="GramE">Solar</span>.... Alguém tem alguma
boa ideia? As premissas aqui seriam: Manutenção mínima; confiabilidade;
baixo custo.

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">2)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>Ainda dentro do tema energia, estamos lutando com o
código para entrar em <span class="SpellE">Deep</span> <span
class="SpellE">Sleep</span>, acordar e enviar dados, mas creio que já
estamos quase prontos, precisamos testar mais um pouco para garantir.

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">3)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>Para a coleta dos dados, estamos estudando como
montar uma API. O ideal seria receber os dados de todas as estações em
real time e ofertar os mesmos dados de forma estruturada também em real
time. Hoje estamos utilizando a infraestrutura de dados do <span
class="SpellE">BigQuery</span> para conseguir fazer isso, mas não é uma
solução fechada. Aceitamos sugestões =)

<span style="mso-bidi-font-family:
Calibri;mso-bidi-theme-font:minor-latin"><span
style="mso-list:Ignore">4)<span
style="font:7.0pt &quot;Times New Roman&quot;">    
</span></span></span>Sempre existe um desafio de design! Como fazer um
hardware Open <span class="SpellE">Source</span>, fácil de <span
class="GramE">replicar</span> mas que garanta alguma precisão? Hoje
temos uma estrutura externa de acrílico cortado a laser e o <span
class="SpellE">tipping</span> <span class="SpellE">bucket</span>
impresso em 3D. A cada protótipo nós mudamos um detalhe ou outro, mas de
maneira geral está funcionando.

 

</div>
