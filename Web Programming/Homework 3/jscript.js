$(document).ready(function() 
{
    $("#butt1").click(function() 
    {
        alert("Hey John!!!\nGazooks! It worked!");
    });

    $("#SpongGar").hover(function()
    {
        $(this).css("color", "white");
    },
    function() 
    {
        $(this).css("color", "black");
    });

    $("#butters").hover(function ()
    {
        $(this).html("THIS IS MY FAV OF THE FAVS");
    });

    $("#butt2").click(function ()
    {
        $("#SpongGar").css("color", "white");
        $("#conceded").css("color", "white");
        $("#student").css("color", "white");
        $("#butters").css("color", "white");
        $("#simi").css("color", "white");
    });

    $("#butt3").click(function ()
    {
        $("#SpongGar").css("color", "black");
        $("#conceded").css("color", "black");
        $("#student").css("color", "black");
        $("#butters").css("color", "black");
        $("#simi").css("color", "black");
    })
});

