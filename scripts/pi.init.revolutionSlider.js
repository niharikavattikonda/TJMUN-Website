jQuery(function($){

	//region Revolution Slider
	if($.fn.revolution){
		$('.pi-revolution-slider').revolution({
			delay:9000,
			startwidth:1130,
			startheight:500,
			hideThumbs:10,
			fullWidth:"on",
			forceFullWidth:"on",
			hideTimerBar:"on"
		});
	}
	//endregion

});

