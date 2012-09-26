function newAjax() {
	var xmlhttp = false;
	try {
		xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
	} catch (e) {
		try {
			xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
		} catch (E) {
			xmlhttp = false;
		}
	}
	if (!xmlhttp && typeof XMLHttpRequest != 'undefined') {
		xmlhttp = new XMLHttpRequest();
	}
	return xmlhttp;
}

function encode_form(obj) {
	var res = "";
	elems = document.getElementsByTagName("input");
	for (i=0; i<elems.length; i++) if (elems[i].form == obj) {
		var en = elems[i].name!=''?elems[i].name:elems[i].id;
		var ev = encodeURIComponent(elems[i].value); var et = elems[i].type;
		if (et == "checkbox") {
			if (elems[i].checked) res+=en+"="+ev+"&"; else res +=en+"=&";
		} else
		if (et == "radio") {
			if (elems[i].checked) res+=en+"="+ev+"&";
		} else
		if (et == "text" || et == "password" || et == "submit" || et == "hidden") {
			res+=en+"="+ev+"&";
		}
	}
	elems = document.getElementsByTagName("select");
	for (i=0; i<elems.length; i++) if (elems[i].form == obj) {
		var en = elems[i].name!=''?elems[i].name:elems[i].id;
		var ev = encodeURIComponent(elems[i].value); var et = elems[i].type;
		res+=en+"="+ev+"&";
	}
	return res;
}

function ajax_post(frmid, cbk) {
	var obj = document.getElementById(frmid);
	if (!obj) obj = document.getElementsByName(frmid)[0];
	ajax=newAjax();
	ajax.open("POST", obj.action?obj.action:"ajax/"+frmid,true);
	ajax.onreadystatechange=function() {
		if (ajax.readyState==4 && cbk) cbk(ajax.responseText);
	}
	ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	ajax.send(encode_form(obj));
	return false;
}

function ajax_post_url(url, msg, cbk) {
	ajax=newAjax();
	ajax.open("POST", "ajax/"+url,true);
	ajax.onreadystatechange=function() {
		if (ajax.readyState==4 && cbk) cbk(ajax.responseText);
	}
	ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	ajax.send(msg);
	return false;
}

function ajax_resp(rsp) {
	var json = eval('(' + rsp + ')');
	if (json.errors) {
		var diverr = document.getElementById("errors");
		for (i = 0; i < json.errors.length; i++) {
			var dive;
			if (json.errors[i].id && (dive = document.getElementById(json.errors[i].id))) {
				diverr.removeChild(dive);
			}
			diverr.innerHTML += json.errors[i].text;
		}
	}
	if (json.divs) {
		for (i = 0; i < json.divs.length; i++) {
			var dv = json.divs[i];
			var e = document.getElementById(dv.id)
			if (dv.sclass != null) e.setAttribute("class", dv.sclass);
			if (dv.html != null) e.innerHTML = dv.html;
		}
	}
	//~ if (json.ndivs) {
		//~ for (i = 0; i < json.ndivs.length; i++) {
			//~ var dv = json.ndivs[i];
			//~ txt = '<div' + (dv.sclass ? ' class="'+dv.sclass+'"' : '') 
				//~ + (dv.id ? ' id="'+dv.id+'"' : '') +'>' + (dv.html?dv.html:'') + '</div>';
			//~ if (dv.parent) {
				//~ var pn = document.getElementById(dv.parent);
				//~ pn.innerHTML = txt + pn.innerHTML;
			//~ }
		//~ }
	//~ }
	//~ 
	if (json.events) {
		for (i = 0; i < json.events.length; i++) {
			var ev = json.events[i];
			var e = document.getElementById(ev.id)
			if (ev.evt != null) e.setAttribute(ev.evt, ev.act);
		}
	}
	
	if (json.imgreload) {
		reloadImages(json.imgreload[0]);
		
	}
}


