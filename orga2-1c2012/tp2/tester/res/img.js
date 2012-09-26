var canvases = ["imagen1", "imagen2", "imagen3", "imagen4"];
var images = {};
var currentx = 0;
var currentdx = 0;
var currenty = 0;
var currentdy = 0;
var currentw = 0;
var currentdw = 0;
var currenth = 0;
var currentdh = 0;
var cwidth = 400;
var cheight = 400;
var oldzoom = 1;



function clearCanvas(context, canvas) {
	context.clearRect(0, 0, canvas.width, canvas.height);
	//~ var w = canvas.width;
	//~ canvas.width = 1;
	//~ canvas.width = w;
}

function reloadStart() {
	var loading = document.getElementById("loading");
	loading.innerHTML = "<img src=\"res/spiral.gif\" width=20px height=20px></img>";
	
	
	var select = document.getElementById("imagename");
	imagen = select.value;
	select.disabled = true;
	
	var selectfiltro = document.getElementById("filtroname");
	filtro = selectfiltro.value;
	selectfiltro.disabled = true;
	
	var	denuevo = document.getElementById("denuevo");
	denuevo.disabled = true;
	
	var prelog = document.getElementById("prelog");
	prelog.innerHTML= "Procesando " + filtro + " en " + imagen;
	
	var log = document.getElementById("log");
	log.innerHTML= "";
	
	var postlog = document.getElementById("postlog");
	postlog.innerHTML= "";


	for (canvasid=0; canvasid < canvases.length; canvasid++) {
		var canvas = document.getElementById(canvases[canvasid]);
		var context = canvas.getContext("2d");
		clearCanvas(context, canvas);
	}
	
	
}

function reloadStop() {
	var loading = document.getElementById("loading");
	loading.innerHTML = "";
	var select = document.getElementById("imagename");
	select.disabled = false;
	select = document.getElementById("filtroname");
	select.disabled = false;
	
	var	denuevo = document.getElementById("denuevo");
	denuevo.disabled = false;
	
	var postlog = document.getElementById("postlog");
	postlog.innerHTML= "Filtro procesado con éxito";
}

function moveH(value) {
	for (canvasid=0; canvasid < canvases.length; canvasid++) {
		var canvas = document.getElementById(canvases[canvasid]);
		var context = canvas.getContext("2d");
			
		currentx = ((oldzoom*images[canvasid].width - currentdw)/2 + parseInt(value))/oldzoom;
			
		try{
			context.drawImage(images[canvasid], currentx, currenty, currentw, currenth, currentdx, currentdy, currentdw, currentdh);
		}
		catch (e)
		{
			
		}
	}
	
}

function moveV(value) {
	for (canvasid=0; canvasid < canvases.length; canvasid++) {
		var canvas = document.getElementById(canvases[canvasid]);
		var context = canvas.getContext("2d");

		currenty = ((oldzoom*images[canvasid].height -currentdh)/2 - parseInt(value))/oldzoom;;
			
		try
		{
			context.drawImage(images[canvasid], currentx, currenty, currentw, currenth, currentdx, currentdy, currentdw, currentdh);
		}
		catch (e)
		{
			
		}
		
			
	}
	
}

function zoom(value) {
	var zoom = parseInt(value);
	var w = cwidth;
	var h = cheight;
			
	
	if (zoom <= 0) zoom = -1/(zoom-2);
		
	

	var oldw = currentw;
	var oldh = currenth;
	currentw = w/zoom;
	currenth = w/zoom;
	var scale = 0;
	if (currentw > images[0].width) {
		scale = images[0].width / currentw;
		w = w * scale;
		currentw = images[0].width;
	}
	if (currenth > images[0].height) {
		scale = images[0].height / currenth;
		h = h * scale;
		currenth = images[0].height;
	}

	currentx = currentx + (oldw-currentw)/2;
	currenty = currenty + (oldh-currenth)/2;
	if (currentx < 0) currentx = 0;
	if (currentx > images[0].width - currentw) currentx = images[0].width-currentw;
	if (currenty < 0) currenty = 0;
	if (currenty > images[0].height-currenth) currenty = images[0].height-currenth;
	
	currentdx = cwidth <= images[0].width*zoom ? 0 : currentx + (cwidth - w)/2;
	currentdy = cheight <= images[0].height*zoom ? 0 : currenty + (cheight - h)/2;
	currentdw = w;
	currentdh = h;
	updateSlider(images[0].width, images[0].height, zoom, false);
	oldzoom = zoom;
	for (canvasid=0; canvasid < canvases.length; canvasid++) {
		var canvas = document.getElementById(canvases[canvasid]);
		var context = canvas.getContext("2d");
		if (scale != 0) clearCanvas(context, canvas);
		context.drawImage(images[canvasid], currentx, currenty, currentw, currenth, currentdx, currentdy, currentdw, currentdh);
	}
	
}


function preloadImages(sources, id, canvasid, callback){
	images = {};
	var loadedImages = 0;
	var numImages = 0;
	for (var src in sources) {
		numImages++;
	}
	//get num of sources
	var nimg = 0;
	for (var i = 0; i < numImages; i++) {
		images[nimg] = new Image();
		images[nimg].onload = function(){
			if (++loadedImages >= numImages) {
				callback(images, id, canvasid);
			}
		};
		images[nimg].src = sources[i];
		nimg++;
	}
}
function updateSlider(w, h, zoom, reset) {
	var hslider = document.getElementById("hslider");
	var vslider = document.getElementById("vslider");
	var hmax = (w*zoom - cwidth) /2;
	var vmax = (h*zoom - cheight) /2;
	if (hmax < 0) {
		hslider.value = 0;
		hslider.disabled = true;
	} else {
		hslider.disabled = false;
		hslider.max = hmax;
		hslider.min = -hmax;
		if (reset) {
			hslider.value = 0;
		} else {
			hslider.value = currentx*zoom - hmax;
		}
		
		
	}
	if (vmax < 0) {
		vslider.value = 0;
		vslider.disabled = true;
	} else {
		vslider.disabled = false;
		vslider.max = vmax;
		vslider.min = -vmax;
		if (reset) {
			vslider.value = 0;
		} else {
			vslider.value = vmax - currenty*zoom ;
		}

	}
	if (reset) {
		var zslider = document.getElementById("zslider");
		zslider.value = 1;
	}
}
function reloadImages(imagenes){
	for (canvasid=0; canvasid < canvases.length; canvasid++) {

		preloadImages(imagenes, canvases[canvasid], canvasid, function(images, id, canvasid){
			var canvas = document.getElementById(id);
			var context = canvas.getContext("2d");
			canvas.width = cwidth;
			canvas.height = cheight;
			
			
			
			currentdw = images[canvasid].width > canvas.width ? canvas.width : images[canvasid].width;
			currentdh = images[canvasid].height > canvas.height ? canvas.height : images[canvasid].height;
			
			currentx = (images[canvasid].width - currentdw)/2;
			currenty = (images[canvasid].height -currentdh)/2;
			currentw = currentdw;
			currenth = currentdh;
			currentdx = currentdw != images[canvasid].width ? 0 : currentx + (canvas.width - currentdw)/2;
			currentdy = currentdh != images[canvasid].height ? 0 : currenty + (canvas.height - currentdh)/2;
			updateSlider(images[canvasid].width, images[canvasid].height, 1, true);
			context.drawImage(images[canvasid], currentx, currenty, currentw, currenth, currentdx, currentdy, currentdw, currentdh);
			reloadStop();
		});
	}
};
