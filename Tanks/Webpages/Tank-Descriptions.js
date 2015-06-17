function changeTankImage(id, didMouseEnter) {
  if (didMouseEnter == 1)
    document.getElementById(id).src="Textures/other-tank.png";
  if (didMouseEnter == 0)
    document.getElementById(id).src="Textures/hero-tank.png";
}