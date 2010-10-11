// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_GUI_Client_Core_TreeNode_hpp
#define CF_GUI_Client_Core_TreeNode_hpp

//////////////////////////////////////////////////////////////////////////////

#include <QObject>

#include "Common/CF.hpp"
#include "GUI/Client/Core/CNode.hpp"

#include "GUI/Client/Core/LibClientCore.hpp"

//////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace GUI {
namespace ClientCore {

  ////////////////////////////////////////////////////////////////////////////

  /// @brief Handles a CNode component in the tree.

  class ClientCore_API TreeNode :
      public QObject
  {
    Q_OBJECT

  public:

    /// @brief Constructor.

    /// @param node The node to handle. The pointer can not be @c nullptr.
    /// @param parent Pointer to the parent TreeNode. May be @c nullptr.
    /// @param rowNumber Row number of the node under the parent. Must be
    /// greater or equal to 0.
    TreeNode(CNode::Ptr node, TreeNode * parent, int rowNumber);

    /// @brief Checks whether the node has a parent or not.

    /// A node has a parent if was constructed with a non-null pointer as
    /// @c parent.
    /// @return Returns @c true if the node has parent. Otherwise, returns
    /// @c false.
    bool hasParent() const;

    /// @brief Returns the @e ith child of this node.

    /// If the TreeNode object corresponding to the asked child does not exist
    /// yet, it is created.
    /// @param rowNumber
    /// @return Returns the wanted child, or a @c nullptr pointer if the row
    /// number is not valid (less than 0, or bigger than the number of
    /// child this this node has).
    TreeNode * getChild(int rowNumber);

    /// @brief Gives the node handled by this object
    /// @returns Returns the node handled by this object.
    CNode::Ptr getNode() const;

    /// @brief Gives the parent.
    /// @return Returns the parent. May return a @c nullptr pointer if the
    /// node has no object.
    TreeNode * getParent() const;

    /// @brief Gives the row number.
    /// @return Returns the row number.
    int getRowNumber() const;

    /// @brief Gives the child count.
    /// @return Returns the child count.
    int getChildCount() const;

    /// @brief Gives the node name.

    /// Calling the method is equivalent to
    /// @code node->getNode()->name().str(); @endcode
    /// @return Return the node name.
    inline QString getName() const
    {
      return m_node->name().c_str();
    }

    /// @brief Retrieves a child from its name.

    /// @return Returns the child, or a @c nullptr pointer if no child
    /// as such name.
    TreeNode * getChildByName(const QString & name);

  public slots:

    /// @brief Updates the child internal list.
    /// The method must be called whenever children are added or removed
    /// from the corresponding node.
    /// @warning To avoid consistency issues, the existing list is
    /// cleared and its items are destroyed. This is because the position
    /// of existing elements may have changed. This means that all items
    /// created by @c getChild will have to be recreated again. Thus,
    /// calling this method too often may lead to performance problems.
    void updateChildList();

  private:

    /// @brief Handled node.
    CNode::Ptr m_node;

    /// @brief The parent. May be @c nullptr
    TreeNode * m_parent;

    /// @brief The row number.
    int m_rowNumber;

    /// @brief List of children.

    /// This list is initialized at the right size in the constructor with
    /// @c nullptr pointers (one pointer for each child). Each pointer is
    /// replaced when the corresponding child is built by @c getChild method.
    QList<TreeNode *> m_childNodes;

  }; // class MyTreeItem

  ////////////////////////////////////////////////////////////////////////////

} // namespace ClientCore
} // namespace GUI
} // namespace CF

//////////////////////////////////////////////////////////////////////////////

#endif // CF_GUI_Client_Core_TreeNode_hpp
