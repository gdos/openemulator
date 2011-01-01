
/**
 * OpenEmulator
 * Mac OS X Chooser View Controller
 * (C) 2009 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls a device or template chooser view.
 */

#import "ChooserViewController.h"
#import "ChooserItem.h"

#define SPLIT_VERT_MIN 128
#define SPLIT_VERT_MAX 256
#define SPLIT_HORIZ_MIN 108

@implementation ChooserViewController

- (id)init
{
	self = [super initWithNibName:@"Chooser" bundle:nil];
	
	if (self)
	{
		groups = [[NSMutableArray alloc] init];
		items = [[NSMutableDictionary alloc] init];
	}
	
	return self;
}

- (void)dealloc
{
	[tableCell release];
	
	[groups release];
	[selectedGroup release];
	[items release];
	
	[super dealloc];
}

- (void)setDelegate:(id)theDelegate
{
	chooserDelegate = theDelegate;
}

- (void)reloadData
{
	if (fTableView)
	{
		NSString *group = [self selectedGroup];
		NSString *path = [self selectedItemPath];
		
		[self loadGroups];
		
		[fTableView reloadData];
		[fImageBrowserView reloadData];
		
		[self selectGroup:group andItemWithPath:path];
	}
}

- (void)awakeFromNib
{
	[self loadGroups];
	
	tableCell = [[VerticallyCenteredTextFieldCell alloc] init];
	[tableCell setControlSize:NSSmallControlSize];
	[tableCell setFont:[NSFont labelFontOfSize:[NSFont smallSystemFontSize]]];
	[tableCell setHorizontalInset:5.0];
	
	NSDictionary *titleAttributes;
	titleAttributes = [NSDictionary dictionaryWithObjectsAndKeys:
					   [NSFont messageFontOfSize:11.0f], NSFontAttributeName,
					   [NSColor blackColor], NSForegroundColorAttributeName,
					   nil];
	NSDictionary *subtitleAttributes;
	subtitleAttributes = [NSDictionary dictionaryWithObjectsAndKeys:
						  [NSFont messageFontOfSize:11.0f], NSFontAttributeName,
						  [NSColor whiteColor], NSForegroundColorAttributeName,
						  nil];
	[fImageBrowserView setAllowsEmptySelection:NO];
	[fImageBrowserView setAllowsMultipleSelection:NO];
	[fImageBrowserView setCellsStyleMask:IKCellsStyleTitled];
	[fImageBrowserView setCellSize:NSMakeSize(108, 64)];
	[fImageBrowserView setDelegate:self];
	[fImageBrowserView setDataSource:self];
	[fImageBrowserView setValue:titleAttributes
						 forKey:IKImageBrowserCellsTitleAttributesKey];
	[fImageBrowserView setValue:subtitleAttributes
						 forKey:IKImageBrowserCellsHighlightedTitleAttributesKey];
	
	[fTableView setDelegate:self];
	[fTableView setDataSource:self];
}



- (void)splitView:(NSSplitView *)sender
resizeSubviewsWithOldSize:(NSSize)oldSize
{
	NSArray *subviews = [sender subviews];
	
	NSSize newSize = [sender frame].size;
	float deltaWidth = newSize.width - oldSize.width;
	float deltaHeight = newSize.height - oldSize.height;
	
	for (NSInteger i = 0; i < [subviews count]; i++)
	{
		NSView *subview = [subviews objectAtIndex:i];
		NSRect frame = subview.frame;
		
		if ([sender isVertical])
		{
			frame.size.height += deltaHeight;
			if (i == 1)
				frame.size.width += deltaWidth;
		}
		else
		{
			frame.size.width += deltaWidth;
			if (i == 0)
			{
				frame.size.height += deltaHeight;
				if (frame.size.height < SPLIT_HORIZ_MIN)
					frame.size.height = SPLIT_HORIZ_MIN;
			}
			else
			{
				frame.origin.y += deltaHeight;
				float maxHeight = (newSize.height - [sender dividerThickness] -
								   SPLIT_HORIZ_MIN);
				if (frame.size.height >= maxHeight)
				{
					frame.origin.y += frame.size.height - maxHeight;
					frame.size.height = maxHeight;
				}
			}
		}
		
		[subview setFrame:frame];
	}
}

- (CGFloat)splitView:(NSSplitView *)splitView
constrainMinCoordinate:(CGFloat)proposedMin
		 ofSubviewAt:(NSInteger)dividerIndex
{
	if ((splitView == fVerticalSplitView) && (dividerIndex == 0))
		return SPLIT_VERT_MIN;
	else if ((splitView = fHorizontalSplitView) && (dividerIndex == 0))
		return SPLIT_HORIZ_MIN;
	
	return proposedMin;
}

- (CGFloat)splitView:(NSSplitView *)splitView
constrainMaxCoordinate:(CGFloat)proposedMax
		 ofSubviewAt:(NSInteger)dividerIndex
{
	if ((splitView == fVerticalSplitView) && (dividerIndex == 0))
		return SPLIT_VERT_MAX;
	
	return proposedMax;
}



- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{
	return [groups count];
}

- (id)tableView:(NSTableView *)aTableView
objectValueForTableColumn:(NSTableColumn *)aTableColumn
			row:(NSInteger)rowIndex
{
	return [groups objectAtIndex:rowIndex];
}

- (NSCell *)tableView:(NSTableView *)tableView
dataCellForTableColumn:(NSTableColumn *)tableColumn
				  row:(NSInteger)row
{
	return tableCell;
}

- (void)tableViewSelectionDidChange:(NSNotification *)aNotification
{
	if (selectedGroup)
	{
		[selectedGroup release];
		selectedGroup = nil;
	}
	NSInteger rowIndex = [fTableView selectedRow];
	if (rowIndex != -1)
		selectedGroup = [[groups objectAtIndex:rowIndex] copy];
	
	[fImageBrowserView reloadData];
	[fImageBrowserView setSelectionIndexes:[NSIndexSet indexSetWithIndex:0]
					  byExtendingSelection:NO];
}



- (NSUInteger)numberOfItemsInImageBrowser:(IKImageBrowserView *)aBrowser
{
	if (!selectedGroup)
		return 0;
	
	if (![items objectForKey:selectedGroup])
		[self loadItems];
	
	return [[items objectForKey:selectedGroup] count];
}

- (id)imageBrowser:(IKImageBrowserView *)aBrowser itemAtIndex:(NSUInteger)index
{
	if (!selectedGroup)
		return nil;
	
	return [[items objectForKey:selectedGroup] objectAtIndex:index];
}

- (void)imageBrowserSelectionDidChange:(IKImageBrowserView *)aBrowser
{
	NSString *label = @"";
	NSImage *image = nil;
	NSString *description = @"";
	
	NSUInteger index = [[fImageBrowserView selectionIndexes] firstIndex];
	if (index != NSNotFound)
	{
		ChooserItem *item = [self imageBrowser:fImageBrowserView
								   itemAtIndex:index];
		label = [item imageTitle];
		image = [item imageRepresentation];
		description = [item description];
	}
	[fSelectedItemLabelView setStringValue:label];
	[fSelectedItemImageView setImage:image];
	[fSelectedItemDescriptionView setStringValue:description];
	
	if ([chooserDelegate respondsToSelector:@selector(chooserSelectionDidChange:)])
		[chooserDelegate chooserSelectionDidChange:self];
}

- (void)imageBrowser:(IKImageBrowserView *)aBrowser
cellWasDoubleClickedAtIndex:(NSUInteger)index
{
	if ([chooserDelegate respondsToSelector:@selector(chooserItemWasDoubleClicked:)])
		[chooserDelegate chooserItemWasDoubleClicked:self];
}



- (void)loadItems
{
}

- (void)loadGroups
{
}

- (void)selectGroup:(NSString *)group
	andItemWithPath:(NSString *)path
{
	if (![groups count])
	{
		[fTableView selectRowIndexes:[NSIndexSet indexSet]
				byExtendingSelection:NO];
		
		[chooserDelegate chooserSelectionDidChange:self];
		return;
	}
	
	NSInteger rowIndex = 0;
	if ([groups containsObject:group])
		rowIndex = [groups indexOfObject:group];
	[fTableView selectRowIndexes:[NSIndexSet indexSetWithIndex:rowIndex]
			byExtendingSelection:NO];
	
	NSInteger itemIndex = 0;
	NSArray *groupItems = [items objectForKey:group];
	for (NSInteger i = 0; i < [groupItems count]; i++)
	{
		ChooserItem *item = [groupItems objectAtIndex:i];
		if ([[item edlPath] compare:path] == NSOrderedSame)
			itemIndex = i;
	}
	[fImageBrowserView setSelectionIndexes:[NSIndexSet indexSetWithIndex:itemIndex]
					  byExtendingSelection:NO];
	[fImageBrowserView scrollIndexToVisible:itemIndex];
}

- (NSString *)selectedGroup
{
	if (selectedGroup)
		return [[selectedGroup copy] autorelease];
	else
		return nil;
}

- (NSString *)selectedItemPath
{
	NSUInteger imageIndex = [[fImageBrowserView selectionIndexes] firstIndex];
	if (imageIndex == NSNotFound)
		return nil;
	
	ChooserItem *item = [self imageBrowser:fImageBrowserView
							   itemAtIndex:imageIndex];
	return [[[item edlPath] copy] autorelease];
}

@end
