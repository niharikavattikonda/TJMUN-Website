<?php

class FormMaker
{
	private $formHtml = "";
	private $postValues;
	private $databaseValues;
	private $submitTask = "submit";

	public function __construct($id, $action, $method, $submitTask=null, $postValues = null, $databaseValues = null)
	{
		
		PageGenerator::addModuleStyle("formMaker.css");

		if($submitTask != null) {
			$this->submitTask = $submitTask;
		}

		$this->postValues = $postValues;
		$this->databaseValues = $databaseValues;

		$this->formHtml .= "<form class=\"formMaker\" id=\"$id\" action=\"$action\" method=\"$method\"><table class=\"formMaker\">";
	}

	public function getForm()
	{
		return $this->formHtml;
	}

	public function finishForm()
	{
		$this->formHtml .= "</table></form>";
	}

	public function addSpace()
	{
		$this->addHtml("&nbsp;");
	}

	public function addHeader($html)
	{
		$this->addHtml(PageGenerator::getHeader($html));
	}

	public function addSubHeader($html)
	{
		$this->addHtml(PageGenerator::getSubHeader($html));
	}

	public function addMessage($messageHtml)
	{
		$this->addHtml(PageGenerator::getPageMessage($messageHtml));
	}

	public function addError($errorHtml)
	{
		$this->addHtml(PageGenerator::getPageError($errorHtml));
	}

	public function addTextInput($description, $name, $width=null, $id=null, $value=null)
	{
		$inputHtml = "<input class=\"formMaker\" type=\"text\" name=\"$name\"";
		$descriptionHtml = "<label class=\"formMaker\"";

		if($width != null) {
			$inputHtml .= " style=\"width: $width\"";
		}

		if($id == null) {
			$inputHtml .= " id=\"$name\"";
			$descriptionHtml .= " for=\"$name\"";
		} else {
			$inputHtml .= " id=\"$id\"";
			$descriptionHtml .= " for=\"$id\"";
		}

		if($value != null) {
			$inputHtml .= sprintf(" value=\"%s\"", htmlspecialchars(stripslashes($value)));
		} else {
			if(isset($this->postValues[$name])) {
				$inputHtml .= sprintf(" value=\"%s\"", htmlspecialchars(stripslashes($this->postValues[$name])));
			} else if(isset($this->databaseValues[$name])) {
				$inputHtml .= sprintf(" value=\"%s\"", htmlspecialchars(stripslashes($this->databaseValues[$name])));
			}
		}

		$inputHtml .= " />";
		$descriptionHtml .= ">$description</label>";

		$this->addHtmlToColumns($descriptionHtml, $inputHtml);
	}

	public function addPasswordInput($description, $name, $width=null, $id=null)
	{
		$inputHtml = "<input class=\"formMaker\" type=\"password\" name=\"$name\"";
		$descriptionHtml = "<label class=\"formMaker\"";

		if($width != null) {
			$inputHtml .= " style=\"width: $width\"";
		}

		if($id == null) {
			$inputHtml .= " id=\"$name\"";
			$descriptionHtml .= " for=\"$name\"";
		} else {
			$inputHtml .= " id=\"$id\"";
			$descriptionHtml .= " for=\"$id\"";
		}

		$inputHtml .= " />";
		$descriptionHtml .= ">$description</label>";

		$this->addHtmlToColumns($descriptionHtml, $inputHtml);
	}

	public function addCheckboxInput($description, $name, $value, $checked=null, $id=null)
	{
		$inputHtml = "<input class=\"formMaker\" type=\"checkbox\" name=\"$name\" value=\"$value\"";
		$descriptionHtml = "<label class=\"formMaker\"";

		if($checked != null) {
			if($checked) {
				$inputHtml .= " checked=\"checked\"";
			}
		} else if(isset($this->postValues['task']) && $this->postValues['task'] == $this->submitTask) {
			if(isset($this->postValues[$name]) && $this->postValues[$name] == $value) {
				$inputHtml .= " checked=\"checked\"";
			}
		} else if(isset($this->databaseValues[$name]) && $this->databaseValues[$name] == $value) {
			$inputHtml .= " checked=\"checked\"";
		}

		if($id == null) {
			$inputHtml .= " id=\"$name\"";
			$descriptionHtml .= " for=\"$name\"";
		} else {
			$inputHtml .= " id=\"$id\"";
			$descriptionHtml .= " for=\"$id";
		}

		$inputHtml .= " />";
		$descriptionHtml .= ">$description</label>";

		$this->addHtmlToColumns($descriptionHtml, $inputHtml);
	}

	public function addSelect($description, $name, $options, $selected=null, $width=null, $id=null)
	{
		$inputHtml = "<select class=\"formMaker\" name=\"$name\"";
		$descriptionHtml = "<label class=\"formMaker\"";

		if($width != null) {
			$inputHtml .= " style=\"width: $width\"";
		}

		if($id == null) {
			$inputHtml .= " id=\"$name\"";
			$descriptionHtml .= " for=\"$name";
		} else {
			$inputHtml .= " id=\"$id\"";
			$descriptionHtml .= " for=\"$id\"";
		}

		if($selected == null) {
			if(isset($this->postValues[$name])) {
				$selected = $this->postValues[$name];
			} else if(isset($this->databaseValues[$name])) {
				$selected = $this->databaseValues[$name];
			}
		}

		if($selected == null) {
			$inputHtml .= "<option class=\"formMaker\" value=\"\">Please select...</option>";
		}

		foreach($options as $key => $value) {
			$optionHtml = "<option class=\"formMaker\" value=\"$value\"";
			if($selected != null && $value == $selected) {
				$optionHtml .= " selected=\"selected\"";
			}
			$optionHtml .= ">$key</option>";
			$inputHtml .= $optionHtml;
		}

		$inputHtml .= "</select>";
		$descriptionHtml .= ">$description</label>";

		$this->addHtmlToColumns($descriptionHtml, $inputHtml);
	}

	public function addSubmitButton($buttonText="Submit")
	{
		$this->addHtml("<input class=\"formMaker\" type=\"hidden\" name=\"task\" id=\"task\" value=\"$this->submitTask\" /><input type=\"submit\" name=\"submit\" value=\"$buttonText\" class=\"formMaker\" />");
	}

	public function addHtml($html)
	{
		$this->formHtml .= "<tr><td class=\"formMaker formMaker_column\" colspan=\"2\">";
		$this->formHtml .= $html;
		$this->formHtml .= "</td></tr>";
	}

	public function addHtmlToColumns($htmlLeft, $htmlRight)
	{
		$this->formHtml .= "<tr><td class=\"formMaker formMaker_column_left\">$htmlLeft</td><td class=\"formMaker formMaker_column_right\">$htmlRight</td></tr>";
	}
}

?>