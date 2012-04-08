//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"

#include "stb_image.c"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Open1Click(TObject *Sender)
{
        if(OpenDialog1->Execute()) {

		FILE* f = fopen(OpenDialog1->FileName.c_str(), "rb");
		if (!f) {
			ShowMessage("Can't open atlas!");
			return;
		}

                elements.clear();
		// Read count of objects
		int count;
                fread(&count, sizeof count, 1, f);
		// load objects
		for (int i = 0; i < count; i++) {
			AtlasElement* ae = new AtlasElement;
			fread(ae, sizeof(AtlasElement), 1, f);
                        // inverting Y from OpenGL
                        ae->v = (1.0f - ae->v) - ae->vh;
			elements.push_back(ae);
		}

                refreshStatusBar();
                // Filling with characters
                refreshList();
        }
}
//---------------------------------------------------------------------------

void TForm1::refreshStatusBar() {
        /*// Texture Width
        StatusBar1->Panels->Items[0]->Text = "Texture Width: " + IntToStr(font->header.tex_width);
        // Texture Height
        StatusBar1->Panels->Items[1]->Text = "Texture Height: " + IntToStr(font->header.tex_height);
        // Chars Range
        StatusBar1->Panels->Items[2]->Text = "Chars Range: " + IntToStr(font->header.start_char) + "-" + IntToStr(font->header.end_char);
        // Texture Type
        StatusBar1->Panels->Items[3]->Text = "Texture Type: " + (font->texType == 120 ? AnsiString("GL_RGBA") : AnsiString("GL_LUMINANCE_ALPHA"));
*/}


void TForm1::refreshList() {
        ListBox1->Items->Clear();

        for (unsigned int i = 0; i < elements.size(); i++) {
                ListBox1->Items->Add(elements.at(i)->name);
        }
}


void TForm1::refreshImage() {
        PaintBox1->Width = textureWidth * zoom;
        PaintBox1->Height = textureHeight * zoom;

        Image2->Width = textureWidth * zoom;
        Image2->Height = textureHeight * zoom;

        if (imageBytes == NULL) {
                Image2->Picture = NULL;
                return;
        }

        //if (currentCH == 2) {
        if (true) {
                if (! stbi_write_bmp((path + "temp.bmp").c_str(), ow, oh, currentCH, imageBytes ) ) {
                        ShowMessage("Can't save tmp data!");
                        return;
                }

                Image2->Picture->LoadFromFile(AnsiString((path + "temp.bmp").c_str()));
        } else {

                int zoom = 1;
                for (int x = 0; x < ow; x++) {
                        for (int y = 0; y < oh; y++) {
                                int index = (x / zoom) * ow * 4 + (y / zoom) * 4;
                                unsigned char r = (unsigned char)imageBytes[index];
                                unsigned char g = (unsigned char)imageBytes[index+1];
                                unsigned char b = (unsigned char)imageBytes[index+2];

                                SetPixel(Image2->Canvas->Handle,y,x,(TColor)RGB(r, g, b));  //font->tex_bytes[(x / zoom) * 4 + (y / zoom) * 4];
                        }
                }
        }
          
}


void __fastcall TForm1::FormCreate(TObject *Sender)
{
        tmpElement = NULL;
        currentElement = NULL;
        cursorStat = -1;
        zoom = 1;
        draging = false;

        path = string(Application->ExeName.c_str());
	for (int i = 1; i < path.size(); i++) {
		if (path[path.size()-i] == '\\') {
			path = path.substr(0, path.size()-i+1);
			break;
		}
	}        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
        if (ListBox1->ItemIndex < 0)
                return;
        currentElement = elements.at(ListBox1->ItemIndex);

        refreshLabels();

        PaintBox1->Repaint();
        repaintShape();
}
//---------------------------------------------------------------------------


void TForm1::refreshLabels() {
        if (currentElement == NULL)
                return;

        if (RadioGroup1->ItemIndex == 0) {
                Edit1->Text = FloatToStr(currentElement->u);
                Edit2->Text = FloatToStr(currentElement->v);
                Edit3->Text = FloatToStr(currentElement->uh);
                Edit4->Text = FloatToStr(currentElement->vh);
        } else {
                Edit1->Text = FloatToStr(currentElement->u * textureWidth);
                Edit2->Text = FloatToStr(currentElement->v * textureHeight);
                Edit3->Text = FloatToStr(currentElement->uh * textureWidth);
                Edit4->Text = FloatToStr(currentElement->vh * textureHeight);
        }
}


void TForm1::repaintShape() {
        if (! currentElement)
                return;
        TRect r = TRect(currentElement->u * textureWidth * zoom, currentElement->v * textureHeight * zoom, (currentElement->u + currentElement->uh) * textureWidth * zoom, (currentElement->v + currentElement->vh) * textureHeight * zoom);

        PaintBox1->Canvas->Brush->Style = bsSolid;
        PaintBox1->Canvas->Brush->Color = 0x00ff00;
        PaintBox1->Canvas->FrameRect(r);
}

void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{
        repaintShape();
}
//---------------------------------------------------------------------------


void TForm1:: refreshCursorStatus(int x, int y) {
        cursorStat = -1;
        if (! currentElement)
                return;

        float x1 = currentElement->u * textureWidth * zoom;
        float x2 = (currentElement->u + currentElement->uh) * textureWidth * zoom;
        float y1 = currentElement->v * textureHeight * zoom;
        float y2 = (currentElement->v + currentElement->vh) * textureHeight * zoom;

        const float bold = 1 * zoom; 

        // top linr
        if (x >= x1 && x <= x2 && y >= y1 - bold && y <= y1 + bold)
                cursorStat = 0;
        // bottom line
        if (x >= x1 && x <= x2 && y >= y2 - bold && y <= y2 + bold)
                cursorStat = 1;
        // left line
        if (x >= x1 - bold && x <= x1 + bold && y >= y1 && y <= y2)
                cursorStat = 2;
        // left line
        if (x >= x2 - bold && x <= x2 + bold && y >= y1 && y <= y2)
                cursorStat = 3;      
}

void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{

        static int lastX = X;
        static int lastY = Y;
        int dX = X - lastX;
        int dY = Y - lastY;
        lastX = X;
        lastY = Y;

        if (! draging) {
                refreshCursorStatus(X, Y);
        } else {

                // Logic for changing char rect
                if (currentElement) {

                        // Sizing
                        if (ComboBox2->ItemIndex == 0) {
                                // top
                                if (cursorStat == 0) {
                                        currentElement->v += dY * (1.0f / (textureHeight * zoom));
                                        currentElement->vh -= dY * (1.0f / (textureHeight * zoom));
                                } else
                                // bottom
                                if (cursorStat == 1) {
                                        currentElement->vh += dY * (1.0f / (textureHeight * zoom));
                                } else
                                // left
                                if (cursorStat == 2) {
                                        currentElement->u += dX * (1.0f / (textureWidth * zoom));
                                        currentElement->uh -= dX * (1.0f / (textureWidth * zoom));
                                } else
                                // right
                                if (cursorStat == 3) {
                                        currentElement->uh += dX * (1.0f / (textureWidth * zoom));
                                }
                        } else {
                        // Moving
                                // vertical
                                if (cursorStat == 0 || cursorStat == 1) {
                                        currentElement->v += dY * (1.0f / (textureHeight * zoom));
                                        //gchar->ty2 += dY * (1.0f / (font->header.tex_height * zoom));
                                } else
                                // bottom
                                if (cursorStat == 2 || cursorStat == 3) {
                                        currentElement->u += dX * (1.0f / (textureWidth * zoom));
                                        //gchar->tx2 += dX * (1.0f / (font->header.tex_width * zoom));
                                }
                        }


                       refreshLabels();
                       PaintBox1->Repaint();
                       repaintShape();
                }

        }

        if (cursorStat == 0 || cursorStat == 1) {
                PaintBox1->Cursor = crSizeNS;
        } else
        if (cursorStat == 2 || cursorStat == 3) {
                PaintBox1->Cursor = crSizeWE;
        } else {
                PaintBox1->Cursor = crDefault;
        } 
}
//---------------------------------------------------------------------------



void TForm1::applyRelative() {
        if (currentElement == NULL)
                return;

        currentElement->u = StrToFloat(Edit1->Text);
        currentElement->v = StrToFloat(Edit2->Text);
        currentElement->uh = StrToFloat(Edit3->Text);
        currentElement->vh = StrToFloat(Edit4->Text);
        PaintBox1->Repaint();
        repaintShape();
}


void TForm1::applyPixels() {
        if (currentElement == NULL)
                return;

        currentElement->u = StrToFloat(Edit1->Text) / textureWidth;
        currentElement->v = StrToFloat(Edit2->Text) / textureHeight;
        currentElement->uh = StrToFloat(Edit3->Text) / textureWidth;
        currentElement->vh = StrToFloat(Edit4->Text) / textureHeight;
        PaintBox1->Repaint();
        repaintShape();
}


void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
        zoom = ComboBox1->ItemIndex + 1;
        refreshImage();
        repaintShape();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        draging = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        draging = false;         
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Exit1Click(TObject *Sender)
{
        exit(0);        
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 13) {
                if (RadioGroup1->ItemIndex == 0) {
                        applyRelative();
                } else {
                        applyPixels();
                }
        }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
        if (currentElement == NULL)
        return;
        tmpElement = currentElement;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
        if (tmpElement == NULL)
        return;

        currentElement->u = tmpElement->u;
        currentElement->v = tmpElement->v;
        currentElement->uh = tmpElement->uh;
        currentElement->vh = tmpElement->vh;
        refreshLabels();
        PaintBox1->Repaint();
        repaintShape();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Load1Click(TObject *Sender)
{
        if (OpenDialog2->Execute()) {

                loadImage(OpenDialog2->FileName);

                refreshStatusBar();
                refreshImage();
        }
}


void TForm1::loadImage(AnsiString path) {
                int ch;
                int w, h;

	        unsigned char * buff = stbi_load(path.c_str(), &w, &h, &ch, 0);
	        if (!buff) {
                        ShowMessage("Can't open image!");
                        return;
                }

                currentCH = ch;
                imageBytes = buff;
                ow = w;
                oh = h;
                setImageSize(w, h);
}


void TForm1::setImageSize(int w, int h) {
        textureWidth = w;
        textureHeight = h;
        Edit5->Text = IntToStr(w);
        Edit6->Text = IntToStr(h);
}


//---------------------------------------------------------------------------

void __fastcall TForm1::Save1Click(TObject *Sender)
{
        if (OpenDialog1->Execute()) {

                // saving
                FILE* f = fopen(OpenDialog1->FileName.c_str(), "wb");
                if (! f) {
                        ShowMessage("Can't save!");
                        return;
                }

                // write elements count
                int count = elements.size();
                fwrite(&count, sizeof(count), 1, f);

                for (int i = 0; i < count; i++) {
                        // inverting Y for OpenGL
                        AtlasElement tmpAE;
                        tmpAE = *elements.at(i);
                        tmpAE.v = 1.0f - (tmpAE.v + tmpAE.vh);
	                fwrite(&tmpAE, sizeof(AtlasElement), 1, f);
                }
                fclose(f);
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
        AnsiString s = InputBox("New Element", "Enter a Name", "name");
        if (s.Length() > 30) {
                ShowMessage("Name lenght must by less or equal to 30.");
                return;
        }
        AtlasElement* ae = new AtlasElement;
        strcpy(ae->name, s.c_str());
        ae->u = 0.0f;
        ae->v = 0.0f;
        ae->uh = 0.2f;
        ae->vh = 0.2f;
        elements.push_back(ae);
        refreshList();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteButtonClick(TObject *Sender)
{
        if (ListBox1->ItemIndex < 0)
                return;
        currentElement = NULL;
        elements.erase(elements.begin() + ListBox1->ItemIndex);
        refreshList();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
        refreshLabels();        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ApplySizeClick(TObject *Sender)
{
        setImageSize(StrToInt(Edit5->Text), StrToInt(Edit6->Text));
        refreshImage();
        refreshLabels();
}
//---------------------------------------------------------------------------

