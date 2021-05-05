/**
 * \file Aquarium.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "Aquarium.h"
#include "Item.h"
#include "FishBeta.h"
#include "DecorCastle.h"
#include "FishDory.h"
#include "Magikarp.h"
#include "XmlNode.h"

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;

/**
 * Constructor
 */
CAquarium::CAquarium()
{
    mBackground = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/background1.png"));
    if (mBackground->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/background1.png");
    }
}

/**
 * Add an item to the aquarium
 * \param item New item to add
 */
void CAquarium::Add(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

/**
 * Remove an item that's duplicated then move it to the end of the list
 * \param item Item gets removed except if it's in the end
 */
void CAquarium::Remove(std::shared_ptr<CItem> item)
{
    auto loc = find(begin(mItems), end(mItems), item);
    if (loc != end(mItems))
    {
        mItems.erase(loc);
    }
}

/** Draw the aquarium
* \param graphics The GDI+ graphics context to draw on
*/
void CAquarium::OnDraw(Gdiplus::Graphics* graphics)
{
    graphics->DrawImage(mBackground.get(), 0, 0,
        mBackground->GetWidth(), mBackground->GetHeight());

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 16);

    SolidBrush green(Color(0, 64, 0));
    graphics->DrawString(L"Under the Sea!", -1, &font, PointF(2, 2), &green);

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}

/** Test an x,y click location to see if it clicked
* on some item in the aquarium.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}

/**
 * Save the aquarium as a .aqua XML file.
 *
 * Open an XML file and stream the aquarium data to it.
 *
 * \param filename The filename of the file to save the aquarium to
 */
void CAquarium::Save(const std::wstring& filename)
{
    //
    // Create an XML document
    //
    auto root = CXmlNode::CreateDocument(L"aqua");

    // Iterate over all items and save them
    for (auto item : mItems)
    {
        item->XmlSave(root);
    }

    try
    {
        root->Save(filename);
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }
}

/**
* Handle an item node.
* \param node Pointer to XML node we are handling
*/
void CAquarium::XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // A pointer for the item we are loading
    shared_ptr<CItem> item;

    // We have an item. What type?
    wstring type = node->GetAttributeValue(L"type", L"");
    if (type == L"beta")
    {
        item = make_shared<CFishBeta>(this);
    }
    if (type == L"castle")
    {
        item = make_shared<CDecorCastle>(this);
    }
    if (type == L"dory")
    {
        item = make_shared<CFishDory>(this);
    }
    if (type == L"magi")
    {
        item = make_shared<CMagikarp>(this);
    }
    if (item != nullptr)
    {
        item->XmlLoad(node);
        Add(item);
    }
}

/**
 * Load the aquarium from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * \param filename The filename of the file to load the aquarium from.
 */
void CAquarium::Load(const std::wstring& filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Once we know it is open, clear the existing data
        Clear();

        //
// Traverse the children of the root
// node of the XML document in memory!!!!
//
        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"item")
            {
                XmlItem(node);
            }
        }
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }
}

/**
 * Clear the aquarium data.
 *
 * Deletes all known items in the aquarium.
 */
void CAquarium::Clear()
{
    mItems.clear();
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CAquarium::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}