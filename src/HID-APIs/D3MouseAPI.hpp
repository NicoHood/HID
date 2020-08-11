#pragma once

D3MouseAPI::D3MouseAPI(void) : _button0(false)
{
	// Empty
}

void D3MouseAPI::begin(void)
{
	end();
}

void D3MouseAPI::end(void)
{
	_button0 = false;
	_button1 = false;
	_button2 = false;
	rotate("x", 0);
	rotate("y", 0);
	rotate("z", 0);
	move("x", 0);
	move("y", 0);
	move("z", 0);
}

void D3MouseAPI::click(int button)
{
	switch (button)
	{
	case 0:
		_button0 = true;
		update();
		_button0 = false;
		update();
		break;
	case 1:
		_button1 = true;
		update();
		_button1 = false;
		update();
		break;
	case 2:
		_button2 = true;
		update();
		_button2 = false;
		update();
		break;
	}
}

void D3MouseAPI::rotate(String axis, int16_t rotation)
{
	if (axis == "x")
		_xRot = rotation;
	if (axis == "y")
		_yRot = rotation;
	if (axis == "y")
		_zRot = rotation;
}

void D3MouseAPI::move(String axis, int16_t pos)
{
	if (axis == "x")
		_x = pos;
	if (axis == "y")
		_y = pos;
	if (axis == "y")
		_z = pos;
}

void D3MouseAPI::update(void)
{
	HID_D3MouseReport_Data_t report;
	report.button0 = _button0;
	report.button1 = _button1;
	report.button2 = _button2;
	report.xRot = _xRot;
	report.yRot = _yRot;
	report.zRot = _zRot;
	report.xAxis = _x;
	report.yAxis = _y;
	report.zAxis = _z;

	SendReport(&report, sizeof(report));
}

void D3MouseAPI::button0(bool b)
{
	if (b != _button0)
	{
		_button0 = b;
		update();
	}
}

void D3MouseAPI::button1(bool b)
{
	if (b != _button1)
	{
		_button1 = b;
		update();
	}
}

void D3MouseAPI::button2(bool b)
{
	if (b != _button2)
	{
		_button2 = b;
		update();
	}
}

void D3MouseAPI::press(int button)
{
	switch (button)
	{
	case 0:
		button0(true);
		break;
	case 1:
		button1(true);
		break;
	case 2:
		button2(true);
		break;
	}
}

void D3MouseAPI::release(int button)
{
	switch (button)
	{
	case 0:
		button0(false);
		break;
	case 1:
		button1(false);
		break;
	case 2:
		button2(false);
		break;
	}
}

void D3MouseAPI::releaseAll(void)
{
	_button0 = false;
	_button1 = false;
	_button2 = false;
	update();
}

bool D3MouseAPI::isPressed(int button)
{
	switch (button)
	{
	case 0:
		return _button0;
		break;
	case 1:
		return _button1;
		break;
	case 2:
		return _button2;
		break;
	}
}
