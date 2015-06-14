function changeTankImage(id, didMouseEnter) {
  if (didMouseEnter == 1)
    document.getElementById(id).src="../Media/Textures/OtherTank.png";
  if (didMouseEnter == 0)
    document.getElementById(id).src="../Media/Textures/HeroTank.png";
}