const char page1[] PROGMEM = 
   "<!DOCTYPE html>\n"
   "<html>\n"
   "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/>\n"
   "<head>\n"
   "\n"
   "<title>ESP-HVAC</title>\n"
   "<style type=\"text/css\">\n"
   "table,input{\n"
   "border-radius: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -ms-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -o-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -webkit-linear-gradient(top, #efffff, #50a0ff);\n"
   "background-image: linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-clip: padding-box;\n"
   "}\n"
   ".style1 {border-width: 0;}\n"
   ".style2 {text-align: right;}\n"
   ".style5 {\n"
   "border-radius: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -ms-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -o-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -webkit-linear-gradient(top, #ff0000, #ffa0a0);\n"
   "background-image: linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "}\n"
   "body{width:340px;display:block;font-family: Arial, Helvetica, sans-serif;}\n"
   "</style>\n"
   "\n"
   "<script type=\"text/javascript\"><!--\n"
   "var Json,mode,autoMode,heatMode,fanMode,running,fan,humidMode,ovrActive,away,rh\n"
   "var a=document.all\n"
   "var states = new Array('Idle','Cooling','HP Heat','NG Heat')\n"
   "var ws\n"
   "var myToken = localStorage.getItem('myStoredText1')\n"
   "function startEvents()\n"
   "{\n"
   "ws = new WebSocket(\"ws://\"+window.location.host+\"/ws\")\n"
   "ws.onopen = function(evt) { }\n"
   "ws.onclose = function(evt) { alert(\"Connection closed.\"); }\n"
   "\n"
   "ws.onmessage = function(evt) {\n"
   " lines = evt.data.split(';')\n"
   " event=lines[0]\n"
   " data=lines[1]\n"
   " if(event == 'settings')\n"
   " {\n"
   "Json=JSON.parse(data)\n"
   "   mode= +Json.m\n"
   "autoMode= +Json.am\n"
   "heatMode= +Json.hm\n"
   "fanMode= +Json.fm\n"
   "humidMode= +Json.rhm\n"
   "ovrActive= +Json.ot\n"
   "setAtt()\n"
   "a.cooll.value= +Json.c0/10\n"
   "a.coolh.value= +Json.c1/10\n"
   "a.heatl.value= +Json.h0/10\n"
   "a.heath.value= +Json.h1/10\n"
   "a.ovrtime.value= s2t(+Json.ov)\n"
   "a.fantime.value= s2t(+Json.fct)\n"
   "a.awaytemp.value= +Json.ad/10\n"
   "  if( +a.ovrtemp.value==0)\n"
   " a.ovrtemp.value= -2.0\n"
   " }\n"
   " else if(event == 'state')\n"
   " {\n"
   "Json=JSON.parse(data)\n"
   "running= +Json.r\n"
   "fan= +Json.fr\n"
   "rh= +Json.h\n"
   "away=+Json.aw\n"
   "a.time.innerHTML=(new Date(+Json.t*1000)).toLocaleTimeString()\n"
   "a.intemp.innerHTML= (+Json.it/10).toFixed(1)\n"
   "a.rh.innerHTML= (+Json.rh/10).toFixed(1)\n"
   "a.target.innerHTML= (+Json.tt/10).toFixed(1)\n"
   "a.outtemp.innerHTML= (+Json.ot/10).toFixed(1)\n"
   "a.cyctimer.innerHTML=secsToTime(+Json.ct)\n"
   "a.runtotal.value=secsToTime(+Json.rt)\n"
   "a.filter.value=s2t(+Json.fm)\n"
   "a.fan.innerHTML=fan?\"Fan On\":\"Fan Off\"\n"
   "a.run.innerHTML=states[+Json.s]\n"
   "a.hm.innerHTML=rh?\"Humidifier On\":\"Humidifier Off\"\n"
   "setAtt()\n"
   " }\n"
   " else if(event == 'alert')\n"
   " {\n"
   "alert(data)\n"
   " }\n"
   "}\n"
   "}\n"
   "\n"
   "function setVar(varName, value)\n"
   "{\n"
   " ws.send('cmd;{\"key\":\"'+myToken+'\",\"'+varName+'\":'+value+'}')\n"
   "}\n"
   "\n"
   "function setfan(n)\n"
   "{\n"
   "if(n<3) fanMode=n\n"
   "setVar('fanmode',n)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setMode(m)\n"
   "{\n"
   "setVar('mode',mode=m)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setHeatMode(m)\n"
   "{\n"
   "setVar('heatmode',heatMode=m)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setHumidMode(m)\n"
   "{\n"
   "setVar('humidmode',humidMode=m)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setAway()\n"
   "{\n"
   "away=!away\n"
   "ovrActive=false\n"
   "setVar('away',away?1:0)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function rstFlt()\n"
   "{\n"
   "setVar('resetfilter',0)\n"
   "}\n"
   "\n"
   "function rstTot()\n"
   "{\n"
   "setVar('resettotal',0)\n"
   "}\n"
   "\n"
   "function setAtt()\n"
   "{\n"
   "a.runCell.setAttribute('class',running?'style5':'style1')\n"
   "a.hmCell.setAttribute('class',rh?'style5':'style1')\n"
   "a.fAuto.setAttribute('class',fanMode==0?'style5':'')\n"
   "a.fOn.setAttribute('class',fanMode==1?'style5':'')\n"
   "a.fS.setAttribute('class',fanMode==2?'style5':'')\n"
   "a.fan.innerHTML = \"Fan \"+((fanMode==1)?\"On\":(fan?\"On\":\"Off\"))\n"
   "a.fanCell.setAttribute('class',fan?'style5' : 'style1')\n"
   "a.ovrCell.setAttribute('class',away?'style1':(ovrActive?'style5':'style1'))\n"
   "\n"
   "a.mOff.setAttribute('class',mode==0?'style5':'')\n"
   "a.mCool.setAttribute('class',mode==1?'style5':'')\n"
   "a.mHeat.setAttribute('class',mode==2?'style5':'')\n"
   "a.mAuto.setAttribute('class',mode==3?'style5':'')\n"
   "\n"
   "a.hHP.setAttribute('class',heatMode==0?'style5':'')\n"
   "a.hGas.setAttribute('class',heatMode==1?'style5':'')\n"
   "a.hAuto.setAttribute('class',heatMode==2?'style5':'')\n"
   "\n"
   "a.hmOff.setAttribute('class',humidMode==0?'style5':'')\n"
   "a.hmFan.setAttribute('class',humidMode==1?'style5':'')\n"
   "a.hmRun.setAttribute('class',humidMode==2?'style5':'')\n"
   "a.hmAuto1.setAttribute('class',humidMode==3?'style5':'')\n"
   "a.hmAuto2.setAttribute('class',humidMode==4?'style5':'')\n"
   "a.away.setAttribute('class',away?'style5':'')\n"
   "}\n"
   "\n"
   "function incCool(n)\n"
   "{\n"
   "a.coolh.value= +a.coolh.value+n\n"
   "a.cooll.value= +a.cooll.value+n\n"
   "\n"
   "setVar('cooltemph',(+a.coolh.value*10).toFixed())\n"
   "setVar('cooltempl',(+a.cooll.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function incHeat(n)\n"
   "{\n"
   "a.heath.value= +a.heath.value+n\n"
   "a.heatl.value= +a.heatl.value+n\n"
   "\n"
   "setVar('heattemph',(+a.heath.value*10).toFixed())\n"
   "setVar('heattempl',(+a.heatl.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setOvrTemp()\n"
   "{\n"
   "setVar('override',(+a.ovrtemp.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setOvrTemp()\n"
   "{\n"
   "setVar('override',(+a.ovrtemp.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function cancelOvr()\n"
   "{\n"
   "setVar('override',0)\n"
   "}\n"
   "\n"
   "function setVars()\n"
   "{\n"
   " s='cmd;{\"key\":\"'+myToken+'\"'\n"
   " s+=',\"cooltemph\":'+(+a.coolh.value*10).toFixed()\n"
   " s+=',\"cooltempl\":'+(+a.cooll.value*10).toFixed()\n"
   " s+=',\"heattemph\":'+(+a.heath.value*10).toFixed()\n"
   " s+=',\"heattempl\":'+(+a.heatl.value*10).toFixed()\n"
   " s+=',\"overridetime\":'+t2s(a.ovrtime.value)\n"
   " s+=',\"fancycletime\":'+t2s(a.fantime.value)\n"
   " s+=',\"awaydelta\":'+(+a.awaytemp.value*10).toFixed()\n"
   " s+='}'\n"
   " ws.send(s)\n"
   "}\n"
   "\n"
   "function secsToTime( elap )\n"
   "{\n"
   "d=0\n"
   "m=0\n"
   "h=Math.floor(elap/3600)\n"
   "if(h >23)\n"
   "{\n"
   "d=Math.floor(h/24)\n"
   "h-=(d*24)\n"
   "}\n"
   "else\n"
   "{\n"
   "m=Math.floor((elap-(h*3600))/60)\n"
   "s=elap-(h*3600)-(m*60)\n"
   "if(s<10) s='0'+s\n"
   "if(h==0)\n"
   "{\n"
   "if( m < 10) m='  '+m\n"
   "return '    '+m +':'+s\n"
   "}\n"
   "}\n"
   "if(m<10) m='0'+m\n"
   "if(h<10) h='  '+h\n"
   "if(d) return d+'d '+h+'h'\n"
   "return h+':'+m+':'+s\n"
   "}\n"
   "\n"
   "function s2t(elap)\n"
   "{\n"
   "m=Math.floor(elap/60)\n"
   "s=elap-(m*60)\n"
   "if(m==0) return s\n"
   "if(s<10) s='0'+s\n"
   "return m+':'+s\n"
   "}\n"
   "\n"
   "function t2s(v)\n"
   "{\n"
   "if(typeof v == 'string') v = (+v.substr(0, v.indexOf(':'))*60) + (+v.substr(v.indexOf(':')+1))\n"
   "return v\n"
   "}\n"
   "//--></script>\n"
   "</head>\n"
   "<body onload=\"{\n"
   " myStorage3 = localStorage.getItem('myStoredText3')\n"
   " if(myStorage3  != null)\n"
   "document.getElementById('ovrtemp').value=myStorage3\n"
   " startEvents()\n"
   "}\">\n"
   "<strong><em>CuriousTech HVAC Remote</em></strong><br>\n"
   "<font size=4>\n"
   "<p><table style=\"width: 350px; height: 22px;\" cellspacing=\"0\">\n"
   "<tr>\n"
   "<td>In</td><td><div id=\"intemp\" class=\"style2\">in</div></td><td>&deg</td><td> &gt;</td>\n"
   "<td><div id=\"target\" class=\"style2\">trg</div></td><td>&deg</td>\n"
   "<td><div id=\"rh\" class=\"style2\">rh</div></td><td>%</td>\n"
   "<td>Out</td><td><div id=\"outtemp\" class=\"style2\">out</div></td><td>&deg</td>\n"
   "</tr>\n"
   "</table>\n"
   "</font></p>\n"
   "<table style=\"width: 350px\" cellspacing=\"0\" cellpadding=\"0\">\n"
   "<tr>\n"
   "<td id=\"fanCell\"><div id=\"fan\">Fan Off</div></td>\n"
   "<td align=\"right\"><input type=\"button\" value=\"Auto\" name=\"fAuto\" onClick=\"{setfan(0)}\"></td>\n"
   "<td width=\"40\"><input type=\"button\" value=\" On \" name=\"fOn\" onClick=\"{setfan(1)}\"><input type=\"button\" value=\"Cycl\" name=\"fS\" onClick=\"{setfan(2)}\"></td>\n"
   "<td width=300 align=\"right\"><input type=\"submit\" value=\"Settings\" onClick=\"window.location='/settings';\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td id=\"runCell\"><div id=\"run\">Cooling</div></td>\n"
   "<td align=\"right\"><input type=\"button\" value=\" Off \" name=\"mOff\" onClick=\"{setMode(0)}\"></td>\n"
   "<td><input type=\"button\" value=\"Cool\" name=\"mCool\" onClick=\"{setMode(1)}\"><input type=\"button\" value=\"Heat\" name=\"mHeat\" onClick=\"{setMode(2)}\"></td>\n"
   "<td><input type=\"button\" value=\"Auto\" name=\"mAuto\" onClick=\"{setMode(3)}\">\n"
   "&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<input type=\"submit\" value=\"Chart\" onClick=\"window.location='/chart.html';\">\n"
   "</td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>&nbsp</td>\n"
   "<td></td>\n"
   "<td></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Cool Hi</td>\n"
   "<td><input type=text size=3 id=\"coolh\"></td>\n"
   "<td><input type=\"button\" value=\"+1\" onClick=\"{incCool(1)}\"></td>\n"
   "<td><div id=\"time\"></div></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td style=\"width: 81px\">Cool Lo</td>\n"
   "<td style=\"width: 44px\"><input type=text size=3 id=\"cooll\"></td>\n"
   "<td style=\"width: 200px\"><input type=\"button\" value=\" -1\" onClick=\"{incCool(-1)}\"></td>\n"
   "<td><input type=\"button\" value=\" HP \" name=\"hHP\" onClick=\"{setHeatMode(0)}\"><input type=\"button\" value=\"Gas \" name=\"hGas\" onClick=\"{setHeatMode(1)}\"><input type=\"button\" value=\"Auto\" name=\"hAuto\" onClick=\"{setHeatMode(2)}\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Heat Hi</td>\n"
   "<td><input type=text size=3 id=\"heath\"></td>\n"
   "<td><input type=\"button\" value=\"+1\" onClick=\"{incHeat(1)}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Heat Lo</td>\n"
   "<td><input type=text size=3 id=\"heatl\"></td>\n"
   "<td><input type=\"button\" value=\" -1\" onClick=\"{incHeat(-1)}\"></td>\n"
   "<td id=\"hmCell\"><div id=\"hm\">Humidifier Off</div></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td></td>\n"
   "<td></td>\n"
   "<td></td>\n"
   "<td>\n"
   "<input type=\"button\" value=\" Off \" name=\"hmOff\" onClick=\"{setHumidMode(0)}\"><input type=\"button\" value=\"Fan\" name=\"hmFan\" onClick=\"{setHumidMode(1)}\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>ovr Time</td><td><input type=text size=3 id=\"ovrtime\"></td><td><input type=\"button\" value=\"Go \" onClick=\"{localStorage.setItem('myStoredText3', a.ovrtemp.value);setOvrTemp()}\"></td>\n"
   "<td>\n"
   "<input type=\"button\" value=\"Run\" name=\"hmRun\" onClick=\"{setHumidMode(2)}\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td id=\"ovrCell\">Overrd &Delta;</td>\n"
   "<td><input type=text size=3 id=\"ovrtemp\"></td>\n"
   "<td><input type=\"button\" value=\"Stop\" onClick=\"{cancelOvr()}\">\n"
   "</td>\n"
   "<td>\n"
   "<input type=\"button\" value=\" A1 \" name=\"hmAuto1\" onClick=\"{setHumidMode(3)}\"><input type=\"button\" value=\" A2 \" name=\"hmAuto2\" onClick=\"{setHumidMode(4)}\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Freshen</td>\n"
   "<td><input type=text size=3 id=\"fantime\"></td>\n"
   "<td><input type=\"button\" value=\" Go  \" onClick=\"{setfan(3)}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Away &Delta;</td><td><input type=text size=3 id=\"awaytemp\"></td><td><input type=\"button\" value=\"Away\" name=\"away\" onClick=\"{setAway()}\"></td>\n"
   "<td align=\"right\"><input type=\"button\" value=\"Save\" onClick=\"{setVars()}\"></td>\n"
   "</tr>\n"
   "</table><br/>\n"
   "<table style=\"width: 350px\">\n"
   "<tr>\n"
   "<td>Cycle</td><td><div id=\"cyctimer\" style=\"width: 70px\">0</div></td>\n"
   "<td>Total</td><td><input type=\"button\" id =\"runtotal\" value=\"0\" onClick=\"{rstTot()}\"></td>\n"
   "<td>Filter</td><td><input type=\"button\" id =\"filter\" value=\"0\" onClick=\"{rstFlt()}\"></td>\n"
   "</tr>\n"
   "</table>\n"
   "<small>Copyright &copy 2016 CuriousTech.net</small>\n"
   "</body>\n"
   "</html>\n";

const char page2[] PROGMEM = 
   "<!DOCTYPE html>\n"
   "<html>\n"
   "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/>\n"
   "<head>\n"
   "\n"
   "<title>ESP-HVAC</title>\n"
   "<style type=\"text/css\">\n"
   "table,input{\n"
   "border-radius: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -ms-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -o-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -webkit-linear-gradient(top, #efffff, #50a0ff);\n"
   "background-image: linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-clip: padding-box;\n"
   "}\n"
   "input{\n"
   "text-align: right;\n"
   "}\n"
   ".style1 {border-width: 0;}\n"
   ".style2 {text-align: right;}\n"
   ".style5 {\n"
   "border-radius: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -ms-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -o-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -webkit-linear-gradient(top, #ff0000, #ffa0a0);\n"
   "background-image: linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "}\n"
   "body{width:340px;display:block;font-family: Arial, Helvetica, sans-serif;}\n"
   "</style>\n"
   "\n"
   "<script type=\"text/javascript\">\n"
   "<!--\n"
   "\n"
   "var Json,ovrActive,away,rmtMode\n"
   "var a=document.all\n"
   "var states = new Array('Idle','Cooling','HP Heat','NG Heat')\n"
   "var ws\n"
   "function startEvents()\n"
   "{\n"
   "ws = new WebSocket(\"ws://\"+window.location.host+\"/ws\")\n"
   "ws.onopen = function(evt) { }\n"
   "ws.onclose = function(evt) { alert(\"Connection closed.\"); }\n"
   "\n"
   "ws.onmessage = function(evt) {\n"
   " lines = evt.data.split(';')\n"
   " event=lines[0]\n"
   " data=lines[1]\n"
   " Json=JSON.parse(data)\n"
   " if(event == 'settings')\n"
   " {\n"
   "a.humidl.value= +Json.rh0/10\n"
   "a.humidh.value= +Json.rh1/10\n"
   "a.idlemin.value= s2t(+Json.im)\n"
   "a.cycmin.value= s2t(+Json.cn)\n"
   "a.cycmax.value= s2t(+Json.cx)\n"
   "a.thresh.value= +Json.ct/10\n"
   "a.fandelay.value= s2t(+Json.fd)\n"
   "a.fanpre.value= s2t(+Json.fp)\n"
   "a.awaytime.value= s2t(+Json.at)\n"
   "a.heatthr.value= +Json.ht\n"
   "a.ppkwh.value= +Json.ppk / 10000\n"
   "a.ccf.value= +Json.ccf / 1000\n"
   "rmtMode=+Json.ar\n"
   "setAtt()\n"
   " }\n"
   " else if(event == 'state')\n"
   " {\n"
   "away=+Json.aw\n"
   "setAtt()\n"
   " }\n"
   " else if(event == 'alert')\n"
   " {\n"
   "alert(data)\n"
   " }\n"
   "}\n"
   "}\n"
   "\n"
   "function setVar(varName, value)\n"
   "{\n"
   " ws.send('cmd;{\"key\":\"'+a.myToken.value+'\",\"'+varName+'\":'+value+'}')\n"
   "}\n"
   "\n"
   "function setAway()\n"
   "{\n"
   "away=!away\n"
   "setVar('away',away?1:0)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setAtt()\n"
   "{\n"
   "a.rmth1.setAttribute('class',(rmtMode&10)==8?'style5':'')\n"
   "a.rmth2.setAttribute('class',(rmtMode&10)==10?'style5':'')\n"
   "a.rmth3.setAttribute('class',(rmtMode&10)==2?'style5':'')\n"
   "a.rmtl1.setAttribute('class',(rmtMode&5)==4?'style5':'')\n"
   "a.rmtl2.setAttribute('class',(rmtMode&5)==5?'style5':'')\n"
   "a.rmtl3.setAttribute('class',(rmtMode&5)==1?'style5':'')\n"
   "}\n"
   "\n"
   "function setVars()\n"
   "{\n"
   " s='cmd;{\"key\":\"'+a.myToken.value+'\"'\n"
   " s+=',\"cyclethresh\":'+(+a.thresh.value*10).toFixed()\n"
   " s+=',\"eheatthresh\":'+a.heatthr.value\n"
   " s+=',\"humidh\":'+(+a.humidh.value*10).toFixed()\n"
   " s+=',\"humidl\":'+(+a.humidl.value*10).toFixed()\n"
   " s+=',\"fanpostdelay\":'+t2s(a.fandelay.value)\n"
   " s+=',\"fanpretime\":'+t2s(a.fanpre.value)\n"
   " s+=',\"idlemin\":'+t2s(a.idlemin.value)\n"
   " s+=',\"cyclemin\":'+t2s(a.cycmin.value)\n"
   " s+=',\"cyclemax\":'+t2s(a.cycmax.value)\n"
   " s+=',\"awaytime\":'+t2s(a.awaytime.value)\n"
   " s+=',\"ppk\":'+(+a.ppkwh.value*10000).toFixed()\n"
   " s+=',\"ccf\":'+(+a.ccf.value*1000).toFixed()\n"
   " s+='}'\n"
   " ws.send(s)\n"
   "}\n"
   "\n"
   "function incHumid(n)\n"
   "{\n"
   "a.humidh.value= +a.humidh.value+n\n"
   "a.humidl.value= +a.humidl.value+n\n"
   "\n"
   "setVar('humidh',(+a.humidh.value*10).toFixed())\n"
   "setVar('humidl',(+a.humidl.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setRmt(v)\n"
   "{\n"
   "switch(v)\n"
   "{\n"
   "case 1: rmtMode&=0xFD;rmtMode|=8;break;\n"
   "case 2: rmtMode|=10;break;\n"
   "case 3: rmtMode&=0xF7;rmtMode|=2;break;\n"
   "case 4: rmtMode&=0xFE;rmtMode|=4;break;\n"
   "case 5: rmtMode|=5;break;\n"
   "case 6: rmtMode&=0xFB;rmtMode|=1;break;\n"
   "}\n"
   "setVar('rmtflgs',rmtMode)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function secsToTime( elap )\n"
   "{\n"
   "d=0\n"
   "m=0\n"
   "h=Math.floor(elap/3600)\n"
   "if(h >23)\n"
   "{\n"
   "d=Math.floor(h/24)\n"
   "h-=(d*24)\n"
   "}\n"
   "else\n"
   "{\n"
   "m=Math.floor((elap-(h*3600))/60)\n"
   "s=elap-(h*3600)-(m*60)\n"
   "if(s<10) s='0'+s\n"
   "if(h==0)\n"
   "{\n"
   "if( m < 10) m='  '+m\n"
   "return '    '+m +':'+s\n"
   "}\n"
   "}\n"
   "if(m<10) m='0'+m\n"
   "if(h<10) h='  '+h\n"
   "if(d) return d+'d '+h+'h'\n"
   "return h+':'+m+':'+s\n"
   "}\n"
   "\n"
   "function s2t(elap)\n"
   "{\n"
   "m=Math.floor(elap/60)\n"
   "s=elap-(m*60)\n"
   "if(m==0) return s\n"
   "if(s<10) s='0'+s\n"
   "return m+':'+s\n"
   "}\n"
   "\n"
   "function t2s(v)\n"
   "{\n"
   "if(typeof v == 'string') v = (+v.substr(0, v.indexOf(':'))*60) + (+v.substr(v.indexOf(':')+1))\n"
   "return v\n"
   "}\n"
   "//--></script>\n"
   "</head>\n"
   "<body onload=\"{\n"
   " myStorage1 = localStorage.getItem('myStoredText1')\n"
   " if(myStorage1  != null){\n"
   "document.getElementById('myToken').value=myStorage1\n"
   " }\n"
   " startEvents()\n"
   "}\">\n"
   "<strong><em>CuriousTech HVAC Settings</em></strong><br><br>\n"
   "<table style=\"width: 240px\" cellspacing=\"0\" cellpadding=\"0\">\n"
   "<tr>\n"
   "<td style=\"width: 81px\">Threshold</td>\n"
   "<td style=\"width: 44px\"><input type=text size=4 id=\"thresh\"></td>\n"
   "<td style=\"width: 10px\"></td>\n"
   "<td>\n"
   "<input type=\"submit\" value=\"Main\" onClick=\"window.location='/iot';\">\n"
   "</td>\n"
   "</tr>\n"
   "<tr><td>Heat Thr</td><td><input type=text size=4 id=\"heatthr\"></td><td></td><td></td></tr>\n"
   "<tr><td>Humid Hi</td><td><input type=text size=4 id=\"humidh\"></td><td><input type=\"button\" value=\"+1\" onClick=\"{incHumid(1)}\"></td><td></td></tr>\n"
   "<tr><td>Humid Lo</td><td><input type=text size=4 id=\"humidl\"></td><td><input type=\"button\" value=\" -1\" onClick=\"{incHumid(-1)}\"></td><td></td></tr>\n"
   "<tr><td>Pre Fan</td>\n"
   "<td><input type=text size=4 id=\"fanpre\"></td>\n"
   "<td></td><td></td></tr>\n"
   "<tr><td>Post Fan</td><td><input type=text size=4 id=\"fandelay\"></td><td></td><td></td></tr>\n"
   "<tr><td>Idle Min</td><td><input type=text size=4 id=\"idlemin\"></td><td></td><td></td></tr>\n"
   "<tr><td>cycle Min</td><td><input type=text size=4 id=\"cycmin\"></td><td></td><td></td></tr>\n"
   "<tr><td>cycle Max</td><td><input type=text size=4 id=\"cycmax\"></td><td></td><td></td></tr>\n"
   "<tr><td>Away Lmt</td><td><input type=text size=4 id=\"awaytime\"></td><td></td><td></td></tr>\n"
   "<tr><td>PPKWH</td><td><input type=text size=4 id=\"ppkwh\"></td><td></td><td><input type=\"button\" value=\"Save\" onClick=\"{setVars()}\"></td></tr>\n"
   "<tr><td>CCF</td><td><input type=text size=4 id=\"ccf\"></td><td></td><td></td></tr>\n"
   "<tr><td>Remote Hi</td><td><input type=\"button\" value=\"Remote\" name=\"rmth1\" onClick=\"{setRmt(1)}\"></td>\n"
   "<td><input type=\"button\" value=\"Avg\" name=\"rmth2\" onClick=\"{setRmt(2)}\"></td><td><input type=\"button\" value=\"Main\" name=\"rmth3\" onClick=\"{setRmt(3)}\">\n"
   "</td></tr>\n"
   "<tr><td>Remote Lo</td><td><input type=\"button\" value=\"Remote\" name=\"rmtl1\" onClick=\"{setRmt(4)}\"></td>\n"
   "<td><input type=\"button\" value=\"Avg\" name=\"rmtl2\" onClick=\"{setRmt(5)}\"></td><td><input type=\"button\" value=\"Main\" name=\"rmtl3\" onClick=\"{setRmt(6)}\">\n"
   "</td></tr>\n"
   "</table>\n"
   "<p>\n"
   "<table style=\"width: 240px\">\n"
   "<tr><td>Password</td><td><input id=\"myToken\" name=\"access_token\" type=text size=40 placeholder=\"e6bba7456a7c9\" style=\"width: 110px\">\n"
   "<input type=\"button\" value=\"Set\" onClick=\"{\n"
   " localStorage.setItem('myStoredText1', a.myToken.value)\n"
   " alert(a.myToken.value+' Has been stored')\n"
   "}\">\n"
   "</td>\n"
   "</tr>\n"
   "</table></p>\n"
   "<small>Copyright &copy 2016 CuriousTech.net</small>\n"
   "</body>\n"
   "</html>\n";

const char page_chart[] PROGMEM =
   "<!DOCTYPE html>\n"
   "<html>\n"
   "<head>\n"
   "<title>HVAC Chart</title>\n"
   "<style type=\"text/css\">\n"
   "div,table,input{\n"
   "border-radius: 5px;\n"
   "margin-bottom: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -ms-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -o-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -webkit-linear-gradient(top, #efffff, #50a0ff);background-image: linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-clip: padding-box;\n"
   "}\n"
   ".style5 {\n"
   "border-radius: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -ms-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -o-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -webkit-linear-gradient(top, #ff0000, #ffa0a0);\n"
   "background-image: linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "}\n"
   "body{background:silver;width:800px;display:block;text-align:center;font-family: Arial, Helvetica, sans-serif;}}\n"
   "</style>\n"
   "<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>\n"
   "<script type=\"text/javascript\">\n"
   "var graph;\n"
   "xPadding=30\n"
   "yPadding=50\n"
   "var yRange\n"
   "var Json\n"
   "var a=document.all\n"
   "var ws\n"
   "$(document).ready(function()\n"
   "{\n"
   " myStorage1 = localStorage.getItem('myStoredText1')\n"
   " if(myStorage1  != null) myToken=myStorage1\n"
   " ws = new WebSocket(\"ws://\"+window.location.host+\"/ws\")\n"
   "// ws = new WebSocket(\"ws://192.168.0.105:85/ws\")\n"
   " ws.onopen = function(evt){ws.send('cmd;{sum:0}')}\n"
   " ws.onclose = function(evt){alert(\"Connection closed.\")}\n"
   " ws.onmessage = function(evt){\n"
   "console.log(evt.data)\n"
   "lines = evt.data.split(';')\n"
   "event=lines[0]\n"
   "data=lines[1]\n"
   "Json=JSON.parse(data)\n"
   "switch(event)\n"
   "{\n"
   "case 'settings':\n"
   "ppkwh= +Json.ppk/10000\n"
   "ccf= +Json.ccf/1000\n"
   "break\n"
   "case 'state':\n"
   "a.today.innerHTML='Today  E $'+Json.ce+' G $'+Json.cg\n"
   "break\n"
   "case 'alert':\n"
   "alert(data)\n"
   "break\n"
   "case 'sum':\n"
   "ws.send('cmd;{data:0}')\n"
   "mname=Array('Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec')\n"
   "date=new Date()\n"
   "for(i=0;i<12;i++)\n"
   "{\n"
   "div=document.getElementById(\"m\"+i)\n"
   "div.innerHTML=mname[i]+' E $'+Json.mon[i][0]+' G $'+Json.mon[i][1]\n"
   "if(date.getMonth()==i) div.setAttribute('class','style5')\n"
   "}\n"
   "for(i=0;i<31;i++)\n"
   "{\n"
   "div=document.getElementById(\"d\"+i)\n"
   "div.innerHTML=(i+1)+' E $'+Json.day[i][0]+' G $'+Json.day[i][1]\n"
   "if(date.getDate()-1==i) div.setAttribute('class','style5')\n"
   "}\n"
   "break\n"
   "case 'data':\n"
   "tb=Json.tb\n"
   "th=Json.th\n"
   "arr=Json.d\n"
   "break\n"
   "case 'data2':\n"
   "arr=arr.concat(Json.d)\n"
   "break\n"
   "case 'draw':\n"
   "draw()\n"
   "break\n"
   "}\n"
   " }\n"
   " setInterval(function(){ ws.send('cmd;{data:0}'); }, 60000);\n"
   "});\n"
   "\n"
   "function draw(){\n"
   "  graph = $('#graph')\n"
   "  c=graph[0].getContext('2d')\n"
   "\n"
   "  tipCanvas=document.getElementById(\"tip\")\n"
   "  tipCtx=tipCanvas.getContext(\"2d\")\n"
   "  tipDiv=document.getElementById(\"popup\")\n"
   "\n"
   "  c.fillStyle='black'\n"
   "  c.strokeStyle='black'\n"
   "  c.clearRect(0, 0, graph.width(), graph.height())\n"
   "  canvasOffset=graph.offset()\n"
   "  offsetX=canvasOffset.left\n"
   "  offsetY=canvasOffset.top\n"
   "\n"
   "  c.lineWidth=2\n"
   "  c.font='italic 8pt sans-serif'\n"
   "  c.textAlign=\"left\"\n"
   "\n"
   "  c.beginPath() // borders\n"
   "  c.moveTo(xPadding,0)\n"
   "  c.lineTo(xPadding,graph.height()-yPadding)\n"
   "  c.lineTo(graph.width()-xPadding, graph.height()-yPadding)\n"
   "  c.lineTo(graph.width()-xPadding, 0)\n"
   "  c.stroke()\n"
   "\n"
   "  c.lineWidth = 1\n"
   "  // dates\n"
   "  step = Math.floor(arr.length / 15)\n"
   "  if(step == 0) step = 1\n"
   "  for(var i=0; i<arr.length-1; i+=step){\n"
   "c.save()\n"
   "c.translate(getXPixel(i), graph.height()-yPadding+5)\n"
   "c.rotate(0.9)\n"
   "date = new Date((tb-arr[i][0]*10)*1000)\n"
   "c.fillText(date.toLocaleTimeString(),0,0)\n"
   "c.restore()\n"
   "  }\n"
   "\n"
   "  yRange = getMaxY() - getMinY()\n"
   "  // value range\n"
   "  c.textAlign = \"right\"\n"
   "  c.textBaseline = \"middle\"\n"
   "\n"
   "  for(var i = getMinY(); i < getMaxY(); i += (yRange/8) ) {\n"
   "    c.fillText((i/10).toFixed(1), xPadding-6, getYPixel(i))\n"
   "  }\n"
   "\n"
   "  c.fillText('Temp', xPadding-4, 6)\n"
   "  c.fillStyle = \"green\"\n"
   "  c.fillText('Rh', graph.width()-14, 6)\n"
   "\n"
   "  // rh scale\n"
   "  for(i = 0; i < 10; i++){\n"
   "    pos = graph.height()-8-( ((graph.height()-yPadding) / 10) * i )-yPadding\n"
   "    c.fillText(i*10, graph.width() - 14, pos)\n"
   "  }\n"
   "\n"
   "  //threshold\n"
   "  c.fillStyle = 'rgba(200,100,200,0.25)'\n"
   "  c.beginPath()\n"
   "  c.moveTo(getXPixel(0), getYPixel(arr[0][3]+th))\n"
   "\n"
   "  for(i=1; i<arr.length-1; i++)\n"
   "    c.lineTo(getXPixel(i), getYPixel(arr[i][3]+th))\n"
   "  for(i=arr.length-2; i>=0; i--)\n"
   "    c.lineTo(getXPixel(i), getYPixel(arr[i][3]))\n"
   "  c.closePath()\n"
   "  c.fill()\n"
   "\n"
   "  // temp lines\n"
   "  date = new Date((tb-arr[0][0]*10)*1000)\n"
   "  dt = date.getDate()\n"
   "  for(i = 1; i < arr.length; i++){\n"
   "c.strokeStyle = stateColor(arr[i][4])\n"
   "c.beginPath()\n"
   "c.moveTo(getXPixel(i), getYPixel(arr[i][1]))\n"
   "c.lineTo(getXPixel(i-1), getYPixel(arr[i-1][1]))\n"
   "c.stroke()\n"
   "date = new Date((tb-arr[i][0]*10)*1000)\n"
   "if(dt != date.getDate())\n"
   "{\n"
   "  dt = date.getDate()\n"
   "  c.strokeStyle = '#000'\n"
   "  c.beginPath() // borders\n"
   "  c.moveTo(getXPixel(i),0)\n"
   "  c.lineTo(getXPixel(i),graph.height()-yPadding)\n"
   "  c.stroke()\n"
   "}\n"
   "  }\n"
   "\n"
   "  // rh lines\n"
   "  c.strokeStyle = '#0f0'\n"
   "  c.beginPath()\n"
   "  c.moveTo(getXPixel(0), getRHPixel(arr[0][2]))\n"
   "\n"
   "  for(var i = 1; i < arr.length-1; i ++)\n"
   "c.lineTo(getXPixel(i), getRHPixel(arr[i][2]))\n"
   "  c.stroke()\n"
   "\n"
   "  var dots = []\n"
   "for(i = 0; i < arr.length; i ++) {\n"
   "date = new Date((tb-arr[i][0]*10)*1000)\n"
   "dots.push({\n"
   "x: getXPixel(i),\n"
   "y: getYPixel(arr[i][1]),\n"
   "r: 4,\n"
   "rXr: 16,\n"
   "color: \"red\",\n"
   "tip: arr[i][1]/10,\n"
   "tip2: arr[i][2]/10,\n"
   "tip3: date.toLocaleTimeString()+' '\n"
   "})\n"
   "}\n"
   "\n"
   "// request mousemove events\n"
   "graph.mousemove(function(e){handleMouseMove(e);})\n"
   "\n"
   "// show tooltip when mouse hovers over dot\n"
   "function handleMouseMove(e){\n"
   "mouseX=parseInt(e.clientX-offsetX)\n"
   "mouseY=parseInt(e.clientY-offsetY)\n"
   "\n"
   "// Put your mousemove stuff here\n"
   "var hit = false\n"
   "for (i = 0; i < dots.length; i++) {\n"
   "dot = dots[i]\n"
   "dx = mouseX - dot.x\n"
   "dy = mouseY - dot.y\n"
   "if (dx * dx + dy * dy < dot.rXr) {\n"
   "tipCtx.clearRect(0, 0, tipCanvas.width, tipCanvas.height)\n"
   "tipCtx.lineWidth = 2\n"
   "tipCtx.fillStyle = \"#000000\"\n"
   "tipCtx.strokeStyle = '#333'\n"
   "tipCtx.font = 'italic 8pt sans-serif'\n"
   "tipCtx.textAlign = \"left\"\n"
   "\n"
   "tipCtx.fillText( dot.tip + 'F', 4, 15)\n"
   "tipCtx.fillText( dot.tip2 + '%', 4, 29)\n"
   "tipCtx.fillText( dot.tip3, 4, 44)\n"
   "hit = true\n"
   "popup = document.getElementById(\"popup\")\n"
   "popup.style.top = dot.y + \"px\"\n"
   "popup.style.left = (dot.x-60) + \"px\"\n"
   "}\n"
   "}\n"
   "if (!hit) { popup.style.left = \"-200px\" }\n"
   "}\n"
   "}\n"
   "\n"
   "function getMaxY(){\n"
   "var max = 0\n"
   "\n"
   "for(i=0; i<arr.length-1; i++)\n"
   "{\n"
   "if(arr[i][1] > max)\n"
   "  max=arr[i][1]\n"
   "if(arr[i][3]+th>max)\n"
   "  max=arr[i][3]+th\n"
   "}\n"
   "return Math.ceil(max)\n"
   "}\n"
   "\n"
   "function getMinY(){\n"
   "var min = 1500\n"
   "\n"
   "for(i=0; i<arr.length; i++)\n"
   "{\n"
   "if(arr[i][1]<min)\n"
   "  min=arr[i][1]\n"
   "if(arr[i][3]<min)\n"
   "  min=arr[i][3]\n"
   "}\n"
   "return Math.floor(min)\n"
   "}\n"
   " \n"
   "function getXPixel(val){\n"
   "x=(graph.width()-xPadding)-((graph.width()-26-xPadding)/arr.length)*val\n"
   "return x.toFixed()\n"
   "}\n"
   "\n"
   "function getYPixel(val) {\n"
   "y=graph.height()-( ((graph.height()-yPadding)/yRange)*(val-getMinY()))-yPadding\n"
   "return y.toFixed()\n"
   "}\n"
   "\n"
   "function getRHPixel(val) {\n"
   "  return graph.height()-(((graph.height()-yPadding)/1000)*val)-yPadding\n"
   "}\n"
   "\n"
   "function stateColor(s)\n"
   "{\n"
   "  sts=Array('gray','blue','red','red')\n"
   "  if(s==1) return 'cyan'\n"
   "  return sts[s>>1]\n"
   "}\n"
   "\n"
   "function setVar(varName, value)\n"
   "{\n"
   " ws.send('cmd;{\"key\":\"'+myToken+'\",\"'+varName+'\":'+value+'}')\n"
   "}\n"
   "\n"
   "</script>\n"
   "<style type=\"text/css\">\n"
   "#wrapper {\n"
   "  width: 800px;\n"
   "  height: 400px;\n"
   "  position: relative;\n"
   "}\n"
   "#graph {\n"
   "  width: 100%;\n"
   "  height: 100%;\n"
   "  position: absolute;\n"
   "  top: 0;\n"
   "  left: 0;\n"
   "}\n"
   "#popup {\n"
   "  position: absolute;\n"
   "  top: 150px;\n"
   "  left: -150px;\n"
   "  z-index: 10;\n"
   "}\n"
   ".style1 {\n"
   "border-style: solid;\n"
   "border-width: 1px;\n"
   "}\n"
   "</style>\n"
   "</head>\n"
   "<body>\n"
   "<div id=\"wrapper\">\n"
   "<canvas id=\"graph\" width=\"800\" height=\"400\"></canvas>\n"
   "<div id=\"popup\"><canvas id=\"tip\" width=\"70\" height=\"45\"></canvas></div>\n"
   "</div>\n"
   "<div id=\"today\"></div>\n"
   "<table cellspacing=1 width=800>\n"
   "<tr><td><div id='d0'></div></td><td><div id='d1'></div></td><td><div id='d2'></div></td><td><div id='d3'></div></td></tr>\n"
   "<tr><td><div id='d4'></div></td><td><div id='d5'></div></td><td><div id='d6'></div></td><td><div id='d7'></div></td></tr>\n"
   "<tr><td><div id='d8'></div></td><td><div id='d9'></div></td><td><div id='d10'></div></td><td><div id='d11'></div></td></tr>\n"
   "<tr><td><div id='d12'></div></td><td><div id='d13'></div></td><td><div id='d14'></div></td><td><div id='d15'></div></td></tr>\n"
   "<tr><td><div id='d16'></div></td><td><div id='d17'></div></td><td><div id='d18'></div></td><td><div id='d19'></div></td></tr>\n"
   "<tr><td><div id='d20'></div></td><td><div id='d21'></div></td><td><div id='d22'></div></td><td><div id='d23'></div></td></tr>\n"
   "<tr><td><div id='d24'></div></td><td><div id='d25'></div></td><td><div id='d26'></div></td><td><div id='d27'></div></td></tr>\n"
   "<tr><td><div id='d28'></div></td><td><div id='d29'></div></td><td><div id='d30'></div></td><td></td></tr>\n"
   "</table>\n"
   "<table cellspacing=1 width=800>\n"
   "<tr><td><div id='m0'></div></td><td><div id='m1'></div></td><td><div id='m2'></div></td><td><div id='m3'></div></td></tr>\n"
   "<tr><td><div id='m4'></div></td><td><div id='m5'></div></td><td><div id='m6'></div></td><td><div id='m7'></div></td></tr>\n"
   "<tr><td><div id='m8'></div></td><td><div id='m9'></div></td><td><div id='m10'></div></td><td><div id='m11'></div></td></tr>\n"
   "</table>\n"
   "</body>\n"
   "</html>\n";
