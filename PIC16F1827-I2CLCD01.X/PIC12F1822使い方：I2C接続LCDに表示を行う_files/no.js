// JavaScript Document

var day = new Date();
var id = ''+day.getFullYear()+day.getDate()+'';
var ie4 = document.all;
var ie5 = document.all && document.getElementById;
var ns4 = document.layers;
var ns6 = document.getElementById && !document.all; 
var auWritten=false;
var mac = (navigator.userAgent.indexOf("Mac") >=0) ? true : false;

function noFrameAu()
{
	try { if (top.location.hostname){ throw "ok"; } else { throw "accesser"; } }
	catch(er) { if (er=="ok") {yfrau = (top.location.href.indexOf(id)>0) ? true : false;} else {yfrau=true;} }
	return yfrau;
}
function writeAu()
{
	document.write("<div id=y_gc_div_adcntr class=y_gcss_ovrtr_au><iframe src=\"http://bc.geocities.yahoo.co.jp/bc/no/" + jps + "\" width=0 height=0 border=0 marginwidth=0 marginheight=0 hspace=0 vspace=0 frameborder=0 scrolling=no>no iframe</iframe></div>");
	auPos('y_gc_div_adcntr');
}
function auPos(divId)
{
	posL = Math.floor(findX() / 2) - 234;
	//posL = findX() - 200;
	if (ns4) {
	posL='1';
	document.layers[divId].visibility = "show";
	document.layers[divId].left = posL;
	} else if (ie5 || ns6) {
	document.getElementById(divId).style.visibility = "visible";
	document.getElementById(divId).style.left = posL;
	} else if (ie4) {
	document.all[divId].style.visibility = "visible";
	document.all[divId].style.left = posL;
	}
}
function isFrameset()
{
	var numFr=0;
	numFr=frames.length;
	numFr=numFr-document.getElementsByTagName("iframe").length;
	isFr=(numFr>0) ? true : false;
	return isFr; 
}
function divAu()
{
//	if (noFrameAu()) {
		if (!isFrameset()) {
			if (inFrame()) {
				if (checkFrame()) {
					writeAu();
					auWritten=true;
					rlPg(true);
				}
			} else {
				writeAu();
				auWritten=true;
				rlPg(true);
			}
		}
//	}
}
function inFrame() {
	inFr=(parent.frames.length != 0) ? true : false;
	return inFr;
}
function findX()
{
	var x=0;
	if (self.innerWidth){x = self.innerWidth;} // ns
	else if (document.documentElement && document.documentElement.clientHeight){x = document.documentElement.clientWidth;} // ie6 strict
	else if (document.body){x = document.body.clientWidth;} // other ie
	return x;
}
function findY()
{
	var y=0;
	if (self.innerHeight){y=self.innerHeight;} // ns
	else if (document.documentElement && document.documentElement.clientHeight){y = document.documentElement.clientHeight;} // ie6 strict
	else if (document.body){y = document.body.clientHeight;} // other ie
	return y;
}
function checkFrame() {
	chFr=(findX() > 400 && findY() > 300) ? true : false;
	return chFr;
}
divAu();
function rlPg(init) {
 	if (init==true) {
		document.pgW = findX();
		onresize=rlPg;
	} else if (window.innerWidth!=document.pgW || document.body.offsetWidth!=document.pgW) {
  	auPos('y_gc_div_adcntr');
  }
}

